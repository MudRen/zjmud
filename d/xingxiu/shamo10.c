// Room: /d/xingxiu/shamo10.c

#include <room.h>
inherit "/d/xingxiu/shamo";

int valid_leave(object me, string dir)
{
	string dest;

	if (dir == "west")
	{
		if (me->add_temp("out_shamo", -1) <= -3)
		{
	     	    	me->move("/d/baituo/gebi");
		     	write("���۵ð���������߳���ɳĮ��\n");
			return -1;
		}
	}

	return ::valid_leave(me, dir);
}
