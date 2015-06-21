#pragma once
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////
// Entity - Component - System microframework.
//	Part of my public game framework available at:
//		http://github.com/arajar/ecs
//
////////////////////////////////////////////////////////////////////////////

namespace ecs
{
	struct world;
	using entity = unsigned int;

	////////////////////////////////////////////////////////////////////////////
	
	struct component
	{
		virtual ~component() {}
	};

	////////////////////////////////////////////////////////////////////////////
	
	struct system
	{
		system(world& world) : m_world(world) {}
		virtual void operator()() const {} // render
		virtual void operator()(float delta) const {} // update

		world& m_world;
	};

	////////////////////////////////////////////////////////////////////////////

	struct world
	{
		std::map<entity, std::vector<component*>> m_entities;
		std::vector<system*> m_systems;

		entity createEntity()
		{
			entity id = static_cast<entity>(m_entities.size()) + 1;
			m_entities[id].reserve(0);
			return id;
		}

		void removeEntity(const entity& id)
		{
			auto found = m_entities.find(id);
			if (found != m_entities.end())
			{
				for (auto& c : m_entities[id])
				{
					delete c;
				}

				m_entities[id].clear();
				m_entities.erase(id);
			}
		}

		void operator()()
		{
			for (auto& s : m_systems)
			{
				// this will call the render function of the system
				(*s)();
			}
		}

		void operator()(float deltaTime)
		{
			for (auto& s : m_systems)
			{
				// this will update the system
				(*s)(deltaTime);
			}
		}

		template<typename c = component>
		c* add(const entity& id)
		{
			if (!has<c>(id))
			{
				auto comp = new c;
				m_entities[id].push_back(comp);
				return comp;
			}
			return nullptr;
		}

		template<typename c = component>
		bool has(const entity& id)
		{
			for (const auto& comp : m_entities[id])
			{
				if (dynamic_cast<c*>(comp))
				{
				 return true; 
				}
			}
			return false;
		}

		template<typename c = component>
		c* get(const entity& id)
		{
			for (auto& comp : m_entities[id])
			{
				auto co = dynamic_cast<c*>(comp);
				if (co) { return co; }
			}
			return nullptr;
		}

		template<typename c = component>
		bool remove(const entity& id)
		{
			for (auto& comp : m_entities[id])
			{
				auto cc = dynamic_cast<c*>(comp);
				if (cc)
				{
					m_entities[id].erase(cc);
					delete cc;
					return true;
				}
			}
			return false;
		}

		template<typename s = system>
		s* add()
		{
			auto sys = new s(*this);
			m_systems.push_back(sys);
			return sys;
		}

		template<typename s = system>
		bool has() const
		{
			for (const auto& sys : m_systems)
			{
				if (dynamic_cast<s*>(sys)) { return true; }
			}
			return false;
		}

		template<typename s = system>
		s* get()
		{
			system* sys = nullptr;
			for (const auto& sys : m_systems)
			{
				sys = dynamic_cast<s*>(sys);
				if (sys) { break; }
			}
			return sys;
		}

		template<typename s = system>
		bool remove()
		{
			for (auto& system : m_systems)
			{
				auto sys = dynamic_cast<s*>(system);
				if (sys) { m_systems.erase(sys); return true; }
			}
			return false;
		}

		template<typename c>
		bool search(std::vector<entity>& vec, entity en)
		{
			for (auto& co : m_entities[en])
			{
				auto c0 = dynamic_cast<c*>(co);
				if (c0)
				{
					vec.push_back(en);
					return true;
				}
			}
			return false;
		}

		template<typename c, typename A>
		std::vector<entity> search()
		{
			std::vector<entity> vec;
			for (auto& e : m_entities)
			{
				if (get<c>(e.first) && search<A>(vec, e.first))
				{
					continue;
				}
			}
			return vec;
		}

		template<typename c, typename A, typename B>
		std::vector<entity> search()
		{
			std::vector<entity> vec;
			for (auto& e : m_entities)
			{
				if (get<c>(e.first) && search<A>(vec, e.first) && search<B>(vec, e.first))
				{
					continue;
				}
			}
			return vec;
		}

		template<typename c, typename A, typename B, typename C>
		std::vector<entity> search()
		{
			std::vector<entity> vec;
			for (auto& e : m_entities)
			{
				if (get<c>(e.first) && search<A>(vec, e.first) && search<B>(vec, e.first) && search<C>(vec, e.first))
				{
					continue;
				}
			}
			return vec;
		}

	};
}
