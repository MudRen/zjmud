// Room: /d/xiakedao/road8.c


#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "һ����");
	set("long", @LONG
�������һ���졣�˴�ɽ�����Ƕ��ͣ����Զ����޵׵���Ԩ����
����һ�����ƾ�ʮ�ȵ�����ɽ·�����˵����޲��ľ�������ֻ������
���Ľţ�����һ��С�ĵ�����Ԩ��
LONG );
	set("exits", ([
		"southup"   : __DIR__"wangyun",
		"northdown" : __DIR__"road7",
	]));
	set("outdoors", "xiakedao");
	setup();
}

void init()
{
	int lvl;
	object me = this_player();

	if (! interactive(me))
		return;

	lvl = me->query_skill("dodge", 1);
	if (lvl + random(lvl) <= 40)
	{
		me->receive_damage("qi", 50);
		me->receive_wound("qi",  50);
		message_vision(HIR"$Nһ��С�Ľ���̤�˸��գ�... ��...!"NOR"\n", me);
		me->move(__DIR__"road5");
		tell_object(me, HIR "���ɽ�Ϲ���������ֻ���û����޴����ۣ������˼����ˡ�"NOR"\n");
		message("vision", HIR "ֻ��" + me->name() + "��ɽ�Ϲ�µµ"
				  "�ع������������ڵ��ϰ�������������"NOR"\n",
				  environment(me), me);
	}
}
