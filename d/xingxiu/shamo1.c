// Room: /d/xingxiu/shamo9.c

#include <room.h>
inherit "/d/xingxiu/shamo";

int valid_leave(object me, string dir)
{
	string dest;

       	if (dir == "east")
	{
		if (me->add_temp("out_shamo", 1) >= 3)
		{
	     	    	me->move("/d/xingxiu/silk4");
		     	write("���۵ð���������߳���ɳĮ��\n");
			return -1;
		}
	}

	return ::valid_leave(me, dir);
}
