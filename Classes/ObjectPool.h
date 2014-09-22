#ifndef ObjectPool_h__
#define ObjectPool_h__
#include <queue>
#include <map>
#include <list>
template<typename T>
class ObjectPoolDelegate
{
public:
	virtual T newObject(int type = 0) = 0;
	virtual void deleteObject(T b) = 0;
};



template<typename T>
class SimpleObjectPool 
{
	std::queue<T>  _recycle_list;
	std::vector<T>  _alive_list;
	ObjectPoolDelegate<T> * _delegate;
	bool _managerAlive;
public:
	SimpleObjectPool(ObjectPoolDelegate<T> * delegate , bool managerAlive = true);
	~SimpleObjectPool();
	T get();
	void recycle(T bullet);
	std::vector<T> * getAliveObjects();
};

template<typename T>
SimpleObjectPool<T>::SimpleObjectPool(ObjectPoolDelegate<T> * delegate , bool managerAlive )
{
	_delegate = delegate;
	_managerAlive = managerAlive;
}

template<typename T>
SimpleObjectPool<T>::~SimpleObjectPool()
{
	// remove recycled objects
	while (!_recycle_list.empty())
	{
		T b = _recycle_list.front();
		if (_delegate != NULL)
			_delegate->deleteObject(b);
		_recycle_list.pop();
	}
	// remove alive objects
	if (_managerAlive)
	{
		for (auto ite = _alive_list.begin(); ite != _alive_list.end() ; ite ++)
		{
			if (_delegate != NULL)
				_delegate->deleteObject(*ite);
		}
		_alive_list.clear();
	}
}

template<typename T>
T SimpleObjectPool<T>::get()
{
	T b = NULL;
	if (! _recycle_list.empty())
	{
		b = _recycle_list.front();
		_recycle_list.pop();
	}
	if (b == NULL)
	{
		b = _delegate->newObject();
	}
	if (_managerAlive)
		_alive_list.push_back(b);
	return b;
}
template<typename T>
void SimpleObjectPool<T>::recycle( T bullet )
{
	_recycle_list.push(bullet);
	//remove from alive list 
}


template<typename T>
std::vector<T> * SimpleObjectPool<T>::getAliveObjects()
{
	if (_managerAlive)
		return &_alive_list;
	else
		printf("enable to  set 'managerAlive' true " );
	return NULL;
}


template<typename T>
class ObjectPool
{
	std::map<int , std::queue <T> *>  _id_pools;
	std::map<T , int> _object_ids;
	std::vector<T> _alive_objects ;
	ObjectPoolDelegate<T> * _delegate;
public:
	ObjectPool(ObjectPoolDelegate<T> * delegate);
	~ObjectPool();
	T get(int type);
	void recycle(T o );
	int idOf(T o);
	std::vector<T> * getAliveObjects();
};

template<typename T>
ObjectPool<T>::ObjectPool( ObjectPoolDelegate<T> * delegate )
{
	_delegate = delegate;
}

template<typename T>
ObjectPool<T>::~ObjectPool()
{
	for (auto it = _id_pools.begin(); it != _id_pools.end() ;it ++)
	{
		auto queue = it->second;
		while (!queue->empty())
		{
			T b = queue->front();
			_delegate->deleteObject(b);
			queue->pop();
		}
		delete queue;
	}

	// alive bullets
	for (auto ite = _alive_objects.begin(); ite != _alive_objects.end() ; ite ++)
	{
		_delegate->deleteObject(*ite);
	}
	_id_pools.clear();
	_alive_objects.clear();
	_object_ids.clear();
}

template<typename T>
int ObjectPool<T>::idOf( T o )
{
	return _object_ids[o];
}

template<typename T>
void ObjectPool<T>::recycle(T o )
{
	int type = idOf(o);
	auto pool = _id_pools[type];
	pool->push(o);
}

template<typename T>
std::vector<T> * ObjectPool<T>::getAliveObjects()
{
	return &_alive_objects;
}


template<typename T>
T ObjectPool<T>::get( int type )
{
	std::queue<T> * pool = _id_pools[type];
	if(pool == NULL)
	{
		pool = new std::queue<T>;
		_id_pools[type] = pool;
	}
	T b = NULL;
	if (! pool->empty())
	{
		b = pool->front();
		pool->pop();
	}
	if (b == NULL)
	{
		b = _delegate->newObject(type);
		_object_ids[b] = type;
	}
	_alive_objects.push_back(b);
	return b;
}










#endif // ObjectPool_h__
