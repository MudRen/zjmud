//shilu4.c by river

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ����ʯ���̳ɵ�С·�������������񣬲�ʱ��Щ���˺�Ѿ�ߴ�����
��������ȥ�������߾͵���ǰԺ��һ��Ⱥ����Χ�������֪���ڿ�ʲô����
�߹�ȥ���ܵ����䳡�ˣ�������һ��ƫ����
LONG);
	set("outdoors","���");
	set("no_fight",1);
        set("exits", ([               
		   "west" : __DIR__"dayuan",
		   "east" : __DIR__"wuchang3",
		   "south" : __DIR__"liangong",
        ]));          

        set("objects", ([
        ]));

        setup();
}
