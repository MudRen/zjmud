// Room: /d/xiangyang/westgate2.c
inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "�׻�����");
	set("long", 
"�����������ǵ������ţ�ֻ�������Ϸ����������֡�"HIW"

		      �׻���
"NOR"\n"
"�������ɹ��Ŵ��ַ������ǣ�����������൱���ܣ�һЩ�ٱ�
�������̲�Ҫ�������ǵ��ˡ������Ǻܴ�Ĳݵء�\n"
 );
	set("outdoors", "xiangyang");

	set("exits", ([
		"east"  : __DIR__"westgate1",
	]));
	set("objects", ([
		__DIR__"npc/pi"   : 1,
		__DIR__"npc/bing" : 2,
	]));
	setup();
}

