#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ľ�ô���");
	set("long", @LONG
����һ������ͨ���ĺ�Ժ���ƾɵĴ��ų����ţ���������һ����Ժ��Ժ��
�����Ǽ�����ͨ����ӡ�
LONG );
       set("exits", ([
		"north" : __DIR__"yangliu3",
		"south" : __DIR__"qingmu_dayuan",
	]));

	set("outdoors", "beijing");
	setup();
}

