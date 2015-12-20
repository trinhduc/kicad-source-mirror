/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2015 Cirilo Bernardo <cirilo.bernardo@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file vrmlv2_node.h
 * defines the base class for VRML2.0 nodes
 */

/*
 * Notes on deleting unsupported entities:
 * 1. PROTO: PROTO ProtoName [parameter list] {body}
 *      the parameter list will always have '[]'. So the items
 *      to delete are: String, List, Body
 * 2. EXTERNPROTO: EXTERNPROTO extern protoname [] MFstring
 *      delete: string, string, string, list, list
 * 3. Unsupported node types:  NodeName (Optional DEF RefName) {body}
 *      This scheme should also apply to PROTO'd node types.
 * 4. ROUTE:  ROUTE nodename1.event to nodename2.event
 *      Delete a String 3 times
 * 5. Script: Script { ... }
 */

#ifndef VRML2_NODE_H
#define VRML2_NODE_H

#include <list>
#include <string>

#include "wrlproc.h"


/**
 * Class WRL2NODE
 * represents the base class of all VRML2 nodes
 */
class WRL2NODE
{
protected:
    WRL2NODE* m_Parent;     // pointer to parent node; may be NULL for top level node
    WRL2NODES m_Type;       // type of VRML node
    std::string m_Name;     // name to use for referencing the node by name

    std::list< WRL2NODE* > m_BackPointers;  // nodes which hold a reference to this

public:

    /**
     * Function getNodeTypeID
     * returns the ID based on the given aNodeName or WRL2_INVALID (WRL2_END)
     * if no such node name exists
     */
    WRL2NODES getNodeTypeID( const std::string aNodeName );

    /**
     * Function unlinkChild
     * removes references to an owned child; it is invoked by the child upon destruction
     * to ensure that the parent has no invalid references.
     *
     * @param aNode is the child which is being deleted
     */
    virtual void unlinkChildNode( const WRL2NODE* aNode ) = 0;

    /**
     * Function unlinkRef
     * removes pointers to a referenced node; it is invoked by the referenced node
     * upon destruction to ensure that the referring node has no invalid references.
     *
     * @param aNode is the node which is being deleted
     */
    virtual void unlinkRefNode( const WRL2NODE* aNode ) = 0;

    /**
     * Function addNodeRef
     * adds a pointer to a node which references, but does not own, this node.
     * Such back-pointers are required to ensure that invalidated references
     * are removed when a node is deleted
     *
     * @param aNode is the node holding a reference to this object
     */
    void addNodeRef( WRL2NODE* aNode );

    /**
     * Function delNodeRef
     * removes a pointer to a node which references, but does not own, this node.
     *
     * @param aNode is the node holding a reference to this object
     */
    void delNodeRef( WRL2NODE* aNode );

public:
    WRL2NODE();
    virtual ~WRL2NODE();

    // read data via the given file processor
    virtual bool Read( WRLPROC& proc ) = 0;

    /**
     * Function GetNodeType
     * returns the type of this node instance
     */
    WRL2NODES GetNodeType( void ) const;

    /**
     * Function GetParent
     * returns a pointer to the parent SGNODE of this object
     * or NULL if the object has no parent (ie. top level transform)
     */
    WRL2NODE* GetParent( void );

    /**
     * Function SetParent
     * sets the parent WRL2NODE of this object.
     *
     * @param aParent [in] is the desired parent node
     * @return true if the operation succeeds; false if
     * the given node is not allowed to be a parent to
     * the derived object.
     */
    virtual bool SetParent( WRL2NODE* aParent ) = 0;

    virtual const char* GetName( void );
    virtual bool SetName(const char *aName);

    const char* GetNodeTypeName( WRL2NODES aNodeType ) const;

    /**
     * Function FindNode searches the tree of linked nodes and returns a
     * reference to the first node found with the given name. The reference
     * is then typically added to another node via AddRefNode().
     *
     * @param aNodeName is the name of the node to search for
     * @param aCaller is a pointer to the node invoking this function
     * @return is a valid node pointer on success, otherwise NULL
     */
    virtual WRL2NODE* FindNode( const char *aNodeName, const WRL2NODE *aCaller ) = 0;

    virtual bool AddRefNode( WRL2NODE* aNode ) = 0;

    virtual bool AddChildNode( WRL2NODE* aNode ) = 0;
};

#endif  // VRML2_NODE_H
