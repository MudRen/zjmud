// chanfang2.c ����
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ȫ������������ԡ��������ĵط���Ϊ�˷�����������
�ζ�û�аڷţ������ڵ��¶��˼���С���š�
LONG
	);
	set("exits", ([
		"east" : __DIR__"chanfang3",
		"west" : __DIR__"chanfang1",
		"south" : __DIR__"liangong",
	]));
	set("no_clean_up", 0);
	setup();
}