// tu.c ̫��ͼ

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "̫��ͼ"; }

int perform(object me)
{
	object *obs;
	string msg;
	int damage;
	int ap, dp;
	int flag;
	int i;

	if (userp(me) && me->query("can_perform/taiji-quan/tu") < 10)
		return notify_fail("�㻹�������á�̫��ͼ����\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܴ�ܡ�\n");

	me->clean_up_enemy();
	if (! me->is_fighting())
		return notify_fail("��̫��ͼ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("taiji-quan", 1) < 250)
		return notify_fail("���̫��ȭ������죬����ʹ�á�̫��ͼ����\n");

	if ((int)me->query_skill("taiji-shengong", 1) < 300)
		return notify_fail("���̫������Ϊ�������ߣ��������á�̫��ͼ����\n");

	if ((int)me->query_skill("taoism", 1) < 300)
		return notify_fail("��ĵ�ѧ�ķ���Ϊ�������ߣ��������á�̫��ͼ����\n");

	if ((int)me->query("jingli") < 1000)
		return notify_fail("�����ھ����������޷�ʹ�á�̫��ͼ����\n");

	if ((int)me->query("neili", 1) < 1000)
		return notify_fail("�����������������޷�ʹ�á�̫��ͼ����\n");

	if (objectp(me->query_temp("weapon")) ||
	    objectp(me->query_temp("secondary_weapon")))
		return notify_fail("Ҫʩչ������̫��ͼ��������֡�\n");

	msg = HIM "$N" HIM "��ȻһЦ��˫�����Ữ������Ȧ�ӣ���ʱ���ܵ���"
	      "��������ԴԴ���ϵı�ǣ��������"NOR"\n";
	message_combatd(msg, me);

	me->add("neili", -1000);
	me->add("jingli", -1000);
	me->start_busy(4);
	ap = me->query_skill("taoism", 1) +
	     me->query_skill("taiji-quan", 1) +
	     me->query_skill("taiji-shengong", 1);
	obs = me->query_enemy();
	for (flag = 0, i = 0; i < sizeof(obs); i++)
	{
		dp = obs[i]->query_skill("force") +
		     obs[i]->query_skill("taoism", 1);
		if (ap / 2 + random(ap) > dp)
		{
			switch (random(3))
			{
			case 0:
				tell_object(obs[i], HIY "���֮�����ƺ��ص��˹�ȥ�����磬��"
						    "Ȼ���޷��������ң���Ȼ��ǰ��һ��\n"
						    "��ȫȻ����������ͷһ�ң�����һ���"
						    "ʹ�������������Կ��ƣ�"NOR"\n");
				break;
			case 1:
				tell_object(obs[i], HIW "����ǰһ�н�����ģ�������������ǵ�"
						    "���ɾ���Ȼ����ȴ������ϢԽ��Խ�ң�\n"
						    "��֫һ����ʹ������Ҫվ����ס��"NOR"\n");
				break;
			default:
				tell_object(obs[i], HIR "����ߺ�Ȼ����һ���������ۼ������"
						    "��紸����������㲻�����һ����\n"
						    "�������¶�����ʹ����ֻ�и������ȡ�"NOR"\n");
				break;
			}
			// receive damage of qi
			//damage = obs[i]->query("max_qi");
			damage = me->query("max_qi");
			damage = damage * (15 + random(6)) / 100;
			obs[i]->receive_damage("qi", damage, me);
			obs[i]->receive_wound("qi", damage / 2, me);

			// receive damage of jing
			//damage = obs[i]->query("max_jing");
			damage = me->query("max_jing");
			damage = damage * (15 + random(6)) / 100;
			obs[i]->receive_damage("jing", damage, me);
			obs[i]->receive_wound("jing", damage / 3, me);

			switch (random(3))
			{
			case 0:
				msg = HIM "ֻ��" + obs[i]->name() +
				      HIM "�����㵸���������ԣ���"
				      "Ȼ���һ������Ѫ��ֹ��"NOR"\n";
				break;
			case 1:
				msg = HIR "ȴ��" + obs[i]->name() +
				      HIR "��ò���ݣ��ƺ�������ʲ"
				      "ô����֮�£�����һ�Σ�Ż��������Ѫ��"NOR"\n";
				break;
			default:
				msg = HIW + obs[i]->name() +
				      HIW "����������һ��������������"
				      "а�����϶��ų���Ѫ����"NOR"\n";
				break;
			}
			obs[i]->start_busy(3);
			message("vision", msg, environment(me), ({ obs[i] }));
			obs[i]->add("neili", -500);
			flag = 1;
		} else
		{
			tell_object(obs[i], HIG "�㷢����ǰ�ľ����ƻ����棬��æ"
					    "Ĭ���ڹ����������š�"NOR"\n");
			obs[i]->add("neili", -200);
		}
		if (obs[i]->query("neili") < 0)
			obs[i]->set("neili", 0);
	}

	if (! flag) 
		message_vision(HIM "Ȼ��û���κ�������$N"
			       HIM "��Ӱ�졣"NOR"\n", me, 0, obs);

	return 1;
}
