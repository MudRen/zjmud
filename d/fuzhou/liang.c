// room: liang.c
//Jay 4/7/96

#include <room.h>

inherit ROOM;

void create()
{ 
       set("short","���ҷ���");
       set("long", @LONG
�����������ҵķ��������¹��ƣ���Χ����Щ��ľͷ��ש�ߡ�
LONG );
	set("exits", ([
		"down" : __DIR__"mishi",
	]));       
	setup();
}
