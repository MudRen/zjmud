// ˫���ͱ�

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "˫��"ZJBR"���"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object leader, object target)
{
	object *member,ob, weapon;
	int i,j,n;
	int max,min,skill;
	string ob_name="";

	member = leader->query_team();
	if (sizeof(member) != 2)
		return notify_fail("�����ǵ��������ˣ���һ����һ�������С�\n");

	j = sizeof (member);
	for (i = 0; i < j; i++)
	{
		ob=member[i];
		if (! ob|| ! living(ob) || ! ob->is_character())
			return notify_fail("�����˭ͬʹ�����ǵ���\n");

		if (ob->query_temp("array/name"))
			return notify_fail("���Ѿ��ڵ������ˡ�\n");

		if (environment(leader) != environment(ob))
			return notify_fail("�����������ˡ�\n");

		if (!ob->query_skill("fanliangyi-dao",1))
			return notify_fail(ob->name() + "�����ᷴ���ǵ�����\n");

		if (ob->is_ghost())
			return notify_fail("ֻ��������˲����鵶��\n");

		if ((int)ob->query("max_neili") < 50)
			return notify_fail(ob->query("name")+"������������\n");

		if (! (weapon = ob->query_temp("weapon")) ||
		    (string)weapon->query("skill_type") != "blade")
			return notify_fail(ob->query("name") + "�����ðѵ���������\n");

		if ((int)ob->query_skill("fanliangyi-dao",1) < 180)
			return notify_fail(ob->query("name") + "�ķ����ǵ���������������\n");

		if ((string)ob->query_skill_mapped("blade") != "fanliangyi-dao")
			return notify_fail(ob->query("name") + "����ʹ�÷����ǵ�����\n");
		if (leader != ob)
			ob_name += " "+ob->name();
	}

//get the average array skill of the team
	n = 0;
	for (i = 0; i < j; i++)
	{
		ob = member[i];
		n += (int)ob->query_skill("fanliangyi-dao", 1);
	}
	n /= 2;

//get the difference of the array skill,
//first get the max and mix skill level of the array
	max = member[0]->query_skill("fanliangyi-dao", 1);
	min = max;
	for (i = 0; i < j; i++)
	{
		skill=member[i]->query_skill("fanliangyi-dao", 1);
		if (skill > max)
			max = skill;
		else
		if (skill < min)
			min = skill;
	}

//and the leader is important
	//n += leader->query_skill("fanliangyi-dao", 1) * 5;
	//n /= max - min + 1;
      if (n>100) n=100;
	for (i = 0; i < j; i++)
	{
		ob=member[i];
		ob->set_temp("no_quit", 1);

		ob->set_temp("array/name", "fanliangyi-dao");
		ob->set_temp("array/level", n);

		ob->add_temp("apply/attack", n);
		ob->add_temp("apply/defense", n);
		ob->add_temp("apply/blade", n*4);
		ob->add_temp("apply/armor", n);
	}
	
	message_combatd(HIG "$N" HIG "����"+ob_name+ HIG " վ�����Ƿ�λ����ʱ��"
			"��֮���Եû�Ȼ��ɡ�����������"NOR"\n", leader);
	
	return 1;
}
