// touxi.c ͵Ϯ
// by King 97.05

#include <ansi.h>

int main(object me, string arg)
{
	object obj;
	int skill, count;

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ֹս����\n");

	if (! arg || ! objectp(obj = present(arg, environment(me))))
		return notify_fail("����͵Ϯ˭��\n");

	if (me->is_chatter())
		return notify_fail("�����������ʲô��͵Ϯ�ģ�\n");

	if (! obj->is_character())
		return notify_fail("�����һ�㣬�ǲ��������\n");

	if (obj->is_fighting(me))
		return notify_fail("���Ѿ���ս�����ˣ�����͵Ϯ��\n");

	if (! living(obj))
		return notify_fail(obj->name() + "���Ѿ������ˣ��㻹��"
				   "����͵Ϯ��\n"); 
	if (obj->query("owner") == me->query("id")) return notify_fail("�㾹Ȼ͵Ϯ�Լ��ĳ��̫���˵��˰ɣ�����\n");
	if (obj == me)
		return notify_fail("͵Ϯ�Լ�������ô�벻����\n");

	if (me->is_busy())
		return notify_fail("��Ķ�����û����ɣ�����͵Ϯ��\n");

	if ((me->query("age")<18 || me->query("combat_exp",1)<200000) && userp(obj))
		return notify_fail("СС��;���ɱ�˷Ż𣿻�������ȥ�ɡ�\n");

	if ((obj->query("age")<18 || obj->query("combat_exp",1)<200000) && userp(obj))
		return notify_fail("��С���Ѷ�Ҫ͵Ϯ���㻹����ȱ��ѽ��\n");

	if (! wizardp(me) && wizardp(obj))
		return notify_fail("��Ҳ�����ͼɱ������Ա��\n");

	if (obj->query_competitor())
		return notify_fail("�˼ұ�����Ҫ͵Ϯ������̫��Ҫ���ˡ�\n");

	tell_object(me, "�������������" + obj->name() +"��\n\n");
	tell_object(obj, CYN + me->name() + "��Ȼ����������"NOR"\n");
	message("vision", CYN + me->name() + "��Ȼ��" + obj->name() +
			  "��ȥ��"NOR"\n", environment(me), ({me, obj}));

	switch (obj->accept_touxi(me))
	{
	case 0:
		return 0;
	case -1:
		return 1;
	}

	count = me->query_str();

	if (userp(me) && userp(obj) && ! obj->is_want_kill(me->query("id")) )
		me->want_kill(obj);
	me->kill_ob(obj);

	if (random(me->query("combat_exp")) < (int)obj->query("combat_exp") / 2)
	{
		me->add_temp("str", count * 4);
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon") );
		me->add_temp("str", - count * 4);
	} else
	{
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
		COMBAT_D->do_attack(me, obj, me->query_temp("weapon"));
	}

	me->start_busy(3);
	obj->kill_ob(me);

	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : touxi <����>
 
���ָ�����������͵Ϯ��͵Ϯ����ʱ����������������ر��ʺ���
����͵��������ߵ����������:)

�������ָ��: fight, kill, hit
HELP
    );
    return 1;
}
