template <class T, class EventTmpl>
void IEventHandler::registerEvent( T* o, void ( T::*evFn )( EventTmpl* ) )
{
_customHandlers[ EventTmpl::StaticGetUID( ) ] = new EventFunctionHandler<T, EventTmpl>( o, evFn );
}

template<class EventTmpl>
void IEventHandler::removeEvent( )
{
  auto it = _customHandlers.find( EventTmpl::StaticGetUID( ) );
  _customHandlers.erase( it );
}

template<class EventTmpl>
bool IEventHandler::hasEvent( )
{
  return _customHandlers.find( EventTmpl::StaticGetUID( ) ) != _customHandlers.end( );
}

template <class T, class EventTmpl>
void EventFunctionHandler<T, EventTmpl>::call( Event* e )
{
  ( _instance->*_fn )( static_cast< EventTmpl* >( e ) );
}
