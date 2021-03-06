/**
 * Copyright (c) 2017, Cristian Rodríguez Bernal
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "IEventHandler.hpp"

namespace seh
{
  IEventHandler::~IEventHandler( )
  {
    CustomHandlers::iterator it = _customHandlers.begin( );
    while( it != _customHandlers.end( ) )
    {
      delete it->second;
      ++it;
    }
    _customHandlers.clear( );
  }

  void IEventHandler::dispatchEvent( Event* e, const bool& propagation )
  {
    CustomHandlers::iterator it = _customHandlers.find( e->GetUID( ) );
    if( it != _customHandlers.end( ) )
    {
      it->second->exec( e );

#ifdef SEH_EVENT_PROPAGATION
      if( propagation )
      {
        if ( !e->isEventPropagation( ) )
        {
          //std::cout << "STOP PROP" << std::endl;
          return;
        }
        for( auto ieh : _childrenHandlers )
        {
          ieh->dispatchEvent( e, propagation );
        }
      }
#endif
      
    }
  }

#ifdef SEH_EVENT_PROPAGATION
  void IEventHandler::addChildEventHandler( IEventHandler* h )
  {
    _childrenHandlers.push_back( h );
  }
#else
  void IEventHandler::addChildEventHandler( IEventHandler* )
  {
    std::cout << "Disable method. Please, enable SEH_EVENT_PROPAGATION option" << std::endl;
  }
#endif

  void IEventHandler::removeEvent( const Event* e )
  {
    CustomHandlers::iterator it = _customHandlers.find( e->GetUID( ) );
    if( it != _customHandlers.end( ) )
    {
      _customHandlers.erase( it );
    }
  }

  void IEventHandler::removeEvent( const std::string& name )
  {
    CustomHandlers::iterator it = _customHandlers.find( name );
    if( it != _customHandlers.end( ) )
    {
      _customHandlers.erase( it );
    }
  }

  bool IEventHandler::hasEvent( const Event* e )
  {
    return _customHandlers.find( e->GetUID( ) ) != _customHandlers.end( );
  }

  bool IEventHandler::hasEvent( const std::string& name )
  {
    return _customHandlers.find( name ) != _customHandlers.end( );
  }
}
