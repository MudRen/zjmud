// laojundian.c �Ͼ���
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�Ͼ���");
	set("long", @LONG
�����ǹ���̫���Ͼ��Ĵ�������������Ͼ��������Ͼ���
����ţ�ϣ������ƶ�ȥ��������������ͯ�ӣ����������������еĵ�
��������שһ�����̳ɣ���ɨ��һ����Ⱦ��
LONG
	);
	set("exits", ([
		"east" : __DIR__"houtang1",
		"south" : __DIR__"tongtiandian",
		"north" : __DIR__"yuanshidian",
		"west" : __DIR__"datang3",
	]));
	set("objects", ([
		CLASS_D("quanzhen") + "/qiu" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir != "east" )
		return 1;

	if(! objectp(guarder = present("qiu chuji", this_object())))
		return 1;

	return guarder->permit_pass(me, dir);
}
