// dating.c

inherit ROOM;

#include <ansi.h>

void create()
{
    set("short", "�һ�ɽׯ����");
    set("long", 
"�������һ�ɽׯ����������������ʮ�ֿ��������й����˸���\n"
"���ҵ��鷨�漣���������۵��������йҵ�һ��������\n\n"
   
BLU "	    �һ�Ӱ�����\n"
    "	    �̺�����������\n\n"
NOR

"�����پ�ͦ�Σ����ƺ�ΰ��\n"
);
	set("exits", ([
	    "north" : __DIR__"qianyuan",
	    "south" : __DIR__"houyuan",
	    "east"  : __DIR__"daojufang",
	    "west"  : __DIR__"wofang" ,
	]));
	set("objects", ([
	    "/kungfu/class/taohua/huang" : 1,
	]) );    
	set("valid_startroom", 1);
	set("no_beg", "1");
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (! objectp(guarder = present("huang yaoshi", this_object())))
	{
		return 1;
	}

	if (dir == "south" || dir == "east")
		return guarder->permit_pass(me, dir);

	return 1;
}
