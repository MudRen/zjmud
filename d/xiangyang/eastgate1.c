// Room: /d/xiangyang/eastgate1.c
inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "��������");
	set("long", 
"�����������ǵĶ����ŵ��ڳ��ţ�ֻ�������Ϸ���������
�֡�"HIG"

		      ������
"NOR"\n"
"�������ɹ��Ŵ��ַ������ǣ�����������൱���ܣ�һЩ�ٱ�
�������̲�Ҫ�������ǵ��ˡ��������ϳ�ͷ��ʯ�ף���������
������\n"
 );
	set("outdoors", "xiangyang");

	set("exits", ([
		"southup" : __DIR__"walle1",
		"northup" : __DIR__"walle2",
		"west"    : __DIR__"eastjie3",
		"east"    : __DIR__"eastgate2",
	]));
	set("objects", ([
		__DIR__"npc/pi"   : 1,
		__DIR__"npc/bing" : 2,
	]));
	setup();
}

