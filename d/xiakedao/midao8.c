// midao8.c �ܵ�

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�ܵ�");
	set("long", @LONG
����һ���������ܵ��������ʯ�����ǻҳ����ܾ�û�������ˡ�
LONG );
	set("exits", ([
		"southdown" : __DIR__"midao7"
	]));
	setup();
}

void init()
{
	object me = this_player();

	if ((int)me->query_skill("dodge", 1) <= 80)
	{
		me->receive_damage("qi", 50);
		me->receive_wound("qi",  50);
		message_vision(HIR "$N" HIR "һ��С�Ĳȵ����ϵ�һ����Ŧ��... ��...��"NOR"\n", me);
		me->move(__DIR__"road3");
		tell_object(me, HIR "���ɽ�Ϲ���������ֻ���û����޴����ۣ������˼����ˡ�"NOR"\n");
		message("vision", HIR "ֻ��" + me->name() + HIR "��ɽ�Ϲ�µµ��"
			"�������������ڵ��ϰ�������������"NOR"\n", environment(me), me);
	}
}
