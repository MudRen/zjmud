#include <ansi.h>

inherit ROOM;

void create()
{
	set("short",HIW "����" NOR);
	set("long", @LONG
������С��԰��һ������������ûʲô������ֻ��һ����ʵ�Ļ�
ũ��������Щ���֣�׬Щ����ѡ�
LONG
	);

	set("exits", ([ 
		"east" : __DIR__"xiaohuayuan",
	]));

	set("objects",([ 
		__DIR__"npc/huanong" : 1,
	])); 

	set("no_fight", 1);   
	setup();
}
