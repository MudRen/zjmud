//qingshe.c ����

#include <ansi.h>

inherit POISON_INSECT;

void create()
{
	set_name("����", ({ "bing can", "can" }) );
	set_weight(100);
	set("race", "Ұ��");
	set("age", 2);
	set("long", "һֻ��������͸��ͨ���Ĳϡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("con", 20);
	set("unit", "ֻ");
	set("limbs", ({ "ͷ��", "����", "β��" }) );
	set("verbs", ({ "bite" }) );

	set("insect_poison", ([
		"level"  : 400,
		"maximum": 400,
	]));

	set("combat_exp", 100);

	setup();
}

// ����������
int absorbed(object me)
{
	object ob;
	int lvl;
	int i;

	//if (! undefinedp(me->query_skill("freezing-force")))
      if (me->query_skill("freezing-force"))
		return 0;

	if ((lvl = me->query_skill("yijinjing", 1)) >= 10)
	{
		message_sort(HIW "$N" HIW "�ۼ�$n" HIW "��������һ�ɱ����ĵ�Ѫˮ�������ؾ���"
			     "���ϣ���Ȼ���û���һ���������������ᣬһʱ��"
			     "��Ϣ���ҡ�$N" HIW "��æ�������׽�񹦣���ʱ���þ�"
			     "��ͨ������Ϣѭ����;����ʱ��ת���������죬��"
			     "���泩�ޱȣ�˵���������졣���׽�񹦺ͱ���"
			     "�ĺ���ͨ�������󷨴��������������Ϻ�����һ��"
			     "�湦����а�����ˮ�𽻼ã���$N" HIW" �������������"NOR"\n",
			     me, this_object());
		CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name() + "�����������˱��Ϻ�����");
		tell_object(me, HIG "�����������˱��Ϻ�����"NOR"\n");
		me->set_skill("freezing-force", lvl);
		me->delete_skill("yijinjing");
	} else
	if (objectp(ob = present("yijin jing", me)))
	{
		message_sort(HIW "$N" HIW "�ۼ�$n" HIW "��������һ�ɱ����ĵ�Ѫˮ�������ؾ���"
			     "���ϣ�����Խ��Խ�䣬ѪҺ���������ˣ����ɵľ�"
			     "��ʧ�롣����ϵĺ����ε�ǿ����$N" HIW "�Զ��껯����"
			     "��Ȼ���ܽ�֮������;��һʱ������ľ����������"
			     "������$N" HIW "���е���һ����������ʱ$N" HIW "�����������"
			     "�����ʪ�������Գ�����ͼ�Σ����м��ˣ����ƹ�"
			     "�죬$N" HIW "��־��Ȼ���壬ڤڤ�а�ͼ����ʩΪ������"
			     "����ͨ������Ϣѭ����;��ֻ�ǻ����������䣬��"
			     "�����Թ�ȥ����������ֻ���û����泩�ޱȣ�˵��"
			     "�������졣���׽�񹦺ͱ��ϵĺ���ͨ��������"
			     "�����������������Ϻ�����һ���湦����а���"
			     "��ˮ�𽻼ã���$N" HIW "�������������"NOR"\n",
			     me, this_object());
		CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name() + "�����������˱��Ϻ�����");
		tell_object(me, HIG "�����������˱��Ϻ�����"NOR"\n");
		me->set_skill("freezing-force", 50);
		me->delete_skill("yijinjing");
	} else
	{
		message_sort(HIG "$N" HIG "�ۼ�$n" HIG "��������һ�ɱ����ĵ�Ѫˮ�������ؾ���"
			     "���ϣ�����Խ��Խ�䣬ѪҺ���������ˣ����ɵľ�"
			     "��ʧ�롣����ϵĺ����ε�ǿ������ʱ��$N" HIG "������"NOR"\n",
			     me, this_object());
		me->unconcious();
		destruct(this_object());
		return -1;
	}

	if (me->can_improve_skill("force"))
		me->improve_skill("force", 250000);
	me->improve_neili(300 + random(300));
	destruct(this_object());
	return -1;
}
