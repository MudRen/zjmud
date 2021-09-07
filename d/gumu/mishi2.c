#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǹ�Ĺ�е����ң������ܲ�͸�磬��ֻ�ܽ���ǽ�ϻ谵�ĵ�
������ǿ�ֱ淽��ǽ�����������ʯ���������ģ��Ӻϵ�����������
�����Դ����ҳ�һ˿��϶��ǽ��(wall)�������һЩ���֡�
LONG );

	set("item_desc", ([
		"��ǽ�ڡ�": WHT "һ����������ʯ���϶��ɵ�ǽ���������źܶ����֣��ƺ�������һЩ�޷����Ͼ����ڡ�"NOR"\n"
			ZJOBACTS2"����:canwu wall\n",
	]) );

	set("exits", ([
		"east" : __DIR__"mishi3",
		"north" : __FILE__,
		"south" : __FILE__,
		"up" : __DIR__"houting",
	]));

	setup();
}

void init()
{
	add_action("do_canwu", "canwu");
}

int do_canwu(string arg)
{
	object me = this_player();
	object ob;
	object ob1;

	if (arg != "wall" && arg != "wall")
		return notify_fail("��Ҫ����ʲô��\n");

	if ((int)me->query("can_perform/yinsuo-jinling/feng"))
		return notify_fail("���Ѿ�ѧ���ˡ����������һ�С�\n");

	if (! (int)me->query_skill("yinsuo-jinling"))
		return notify_fail("������˰��죬����ǽ�ϼ��صĶ�������"
				   "��ϰ����ѧûʲô�ϸ𣬲��򲻳�ʲô��\n");

	if ((int)me->query_skill("yinsuo-jinling", 1) < 130)
		return notify_fail("��������������ⲻ�������򲻳�ʲô��\n");

	if (me->is_busy())
		return notify_fail("���������ڲ����С�\n");

	if ((int)me->query("potential") < 5)
		return notify_fail("���Ǳ�ܲ����ˣ����򲻳�ʲô��\n");

	if ((int)me->query("jing") < 30)
		return notify_fail("��̫ƣ���ˣ���Ϣһ�°ɡ�\n");

	if (random(20) < 18)
	{
		me->receive_damage("jing", 25);
		me->add("potential", -5);
		me->start_busy(2);
		message_vision(WHT "$N" WHT "�����ʯ�ھ�˼���ã���"
			       "����ʯ���������صĶ�����"NOR"\n", me);
		tell_object(me, HIY "��������������˸������⣬��"
			       "�����һ���Ĳ���"NOR"\n");
		return 1;
	} else
	{ 
		me->receive_damage("jing", 25);
		me->add("potential", -5);
		me->start_busy(2);
		message_vision(WHT "$N" WHT "�����ʯ�ھ�˼���ã���"
			       "����ʯ���������صĶ�����"NOR"\n", me);
		tell_object(me, HIY "���á������á���������������"
				"�������塸������������İ��أ�\n\n"
				NOR + HIC "��ѧ���ˡ����������һ��"
				"��"NOR"\n");
		if (me->can_improve_skill("whip"))
			me->improve_skill("whip", 960000);
		if (me->can_improve_skill("parry"))
			me->improve_skill("parry", 960000);
		if (me->can_improve_skill("dodge"))
			me->improve_skill("dodge", 960000);
		if (me->can_improve_skill("yinsuo-jinling"))
			me->improve_skill("yinsuo-jinling", 960000);
		me->set("can_perform/yinsuo-jinling/feng", 1);
	}

	return 1;
}

