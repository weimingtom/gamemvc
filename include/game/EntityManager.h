#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

//------------------------------------------------------------------------
//
//  Name:   EntityManager.h
//
//  Desc:   Singleton class to handle the  management of Entities.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <map>
#include <cassert>
#include <string>

class BaseGameEntity;

//! provide easy access
#define EntityMgr EntityManager::Instance()
/*!
 *  @brief Clase para el manejo de entidades
 *
 *  Contiene todas la entidades existentes en el juego.
 *
 */
class EntityManager
{

  public:
    /*!
     *
     * @return
     */
    static EntityManager* Instance();
    /*!
     * this method stores a pointer to the entity in the std::vector
     * m_Entities at the index position indicated by the entity's ID
     * (makes for faster access)
     *
     * @param NewEntity
     */
    void RegisterEntity( BaseGameEntity* NewEntity );
    /*!
     * returns a pointer to the entity with the ID given as a parameter
     *
     * @param id
     * @return
     */
    BaseGameEntity* GetEntityFromID( int id ) const;
    /*!
     * this method removes the entity from the list
     *
     * @param pEntity
     */
    void RemoveEntity( BaseGameEntity* pEntity );

  private:

    typedef std::map < int, BaseGameEntity* > EntityMap;
    /*!
     *
     * to facilitate quick lookup the entities are stored in a std::map, in which
     * pointers to entities are cross referenced by their identifying number
     */
    EntityMap m_EntityMap;
    //! copy ctor and assignment should be private

    EntityManager()
    {
    }
    EntityManager( const EntityManager& );
    EntityManager& operator=( const EntityManager& );
};

#endif
