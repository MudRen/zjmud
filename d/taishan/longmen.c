// Room: /d/taishan/.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������̩ɽʮ���̵���㡣�˴�ɽ�ƶ��ͣ���ɽ����һ����
С�ĺ����ױ����鵽�¹�֮�С�
LONG );
	set("exits", ([
		"northup" : __DIR__"shengxian",
		"southdown" : __DIR__"wudafu",
	]));
	set("objects", ([
		__DIR__"npc/chi" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

void init()
{
	object me = this_player();
	
	if( random((int)me->query_skill("dodge")) <= 10) 
	{
		me->receive_damage("qi", 50);
		me->receive_wound("qi",  50);
		message_vision(HIR"$Nһ��С�Ľ���̤�˸��գ�... ��...��"NOR"\n", me);
		me->move(__DIR__"daizong");
		tell_object(me, HIR"���ɽ�Ϲ���������ֻ���û����޴����ۣ������˼����ˡ�"NOR"\n");
		message("vision", HIR"ֻ��" + me->query("name") + "��ɽ�Ϲ�µµ�ع������������ڵ��ϰ�������������"NOR"\n", environment(me), me);
	}
}

