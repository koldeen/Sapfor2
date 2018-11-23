#ifndef OBJECT_H
#define OBJECT_H

namespace Object
{
	class IObject
	{
	public:
		virtual IObject* Clone () = 0;
	};
}

#endif