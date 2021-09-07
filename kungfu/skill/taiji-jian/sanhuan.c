
#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��������"; }
string *pfm_type() { return ({ "sword", }); }

int query_cd() { return 4; }

int perform(object me, object target)
{
	object weapon;
	int i;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("̫���������������¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("taiji-jian", 1) < 300)
		return notify_fail("���̫������������죬�޷�ʹ�����������¡���\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷�ʹ�����������¡���\n");

	if (me->query_skill_mapped("sword") != "taiji-jian")
		return notify_fail("��û�м���̫���������޷�ʹ�����������¡���\n");
	if (me->query_skill_mapped("parry") != "taiji-jian")
		return notify_fail("��û�м���̫������Ϊ�м��书���޷�ʹ�����������¡���\n");

      if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->set_temp("tjj/sanhuan", 3);
	for (i = 0; i < 3; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	return 1;
}
