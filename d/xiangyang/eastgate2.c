// Room: /d/xiangyang/eastgate2.c
inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "��������");
	set("long", 
"�����������ǵĶ����ţ�ֻ�������Ϸ����������֡�"HIG"
		      ������
"NOR"\n"
"�������ɹ��Ŵ��ַ������ǣ�����������൱���ܣ�һЩ�ٱ�
�������̲�Ҫ�������ǵ��ˡ������Ǻܴ�Ĳݵء�\n"
 );
	set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : __DIR__"eastgate1",
	]));
	set("objects", ([
		__DIR__"npc/pi"   : 1,
		__DIR__"npc/bing" : 2,
	]));
	setup();
}

