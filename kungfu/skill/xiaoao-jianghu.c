// xiaoao-jianghu.c Ц��������

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa" ||
					usage == "tanqin-jifa"; }

int valid_learn(object me)
{
	if (me->query_skill("tanqin-jifa", 1) < 50 &&
	    me->query_skill("chuixiao-jifa", 1) < 50)
		return notify_fail("��Ĵ����͵��ٵļ���ˮƽ��̫�������������˵�ɣ�\n");

	if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qingxin-pushan", 1) &&
	    me->query_skill("cuhixiao-jifa", 1) < me->query_skill("qingxin-pushan", 1))
		return notify_fail("�����ո����Ĵ����������ټ���֮ǰ�����޷����������Ц����������\n");

	return 1;
}

int practice_skill(object me)
{
	object ob;

	if (! objectp(ob = me->query_temp("handing")) ||
	    ! ob->valid_as_qin() &&
	    ! ob->valid_as_xiao())
		return notify_fail("�����ϼ�û���Ҳû���٣���ô��ϰ��\n");

	if ((int)me->query("jing") < 100)
		return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("������ʵ����̫���ˣ��������ˡ�\n");

	me->receive_damage("jing", 60);
	me->receive_damage("qi", 40);

	return 1;
}

void do_effect(object me)
{
	object *obs;
	object ob;
	string type;
	string other;
	int amount;
	int lvl;
	int i;

	lvl = me->query_skill("xiaoao-jianghu", 1);

	if (lvl < 100)
		return;

	if (previous_object() == find_object(SKILL_D("chuixiao-jifa")))
	{
		type = "xajh/xiao";
		other = "xajh/qin";
	} else
	if (previous_object() == find_object(SKILL_D("tanqin-jifa")))
	{
		type = "xajh/qin";
		other = "xajh/qin";
	} else
		return;

	// special effort
	obs = all_inventory(environment(me));
	for (i = 0; i < sizeof(obs); i++)
	{
		ob = obs[i];
		if (ob == me || ! ob->is_character() || ! living(ob))
			continue;

		if (ob->query_temp("xajh/powerup") ||
		    time() - ob->query_temp(other) > 30 ||
		    ! stringp(ob->query_temp("xajh/player")) ||
		    ob->query_temp("xajh/player") == me->query("id"))
		{
			ob->set_temp(type, time());
			ob->set_temp("xajh/player", me->query("id"));
			ob->set_temp("xajh/player_name", me->name());
			message("visoin", HIG "������" + me->name() +
				HIG "�����ӣ����÷ǳ��Ŀ���������"NOR"\n", ob);
		} else
		{
			// ˫�˺���
			amount = lvl;
			if (amount > ob->query_skill("force"))
				amount = ob->query_skill("force");
			amount /= 6;
			ob->delete_temp(other);
			ob->delete_temp(type);
			ob->add_temp("apply/attack", amount);
			ob->add_temp("apply/dodge", amount);
			ob->set_temp("xajh/powerup", 1);
		
			call_out("remove_effect", lvl / 2, ob, amount);
			message("vision", HIG "������" + me->name() +
				HIG "��" + ob->query_temp("xajh/player_name") +
				"�����Ц��������ֻ�����ĳ����ȣ�������������"NOR"\n", ob);
			ob->delete_temp("xajh/player");
			ob->delete_temp("xajh/player_name");
		}
	}
}

void remove_effect(object me, int amount)
{
	if (! objectp(me))
		return;
	if ((int)me->query_temp("xajh/powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/dodge", -amount);
		me->delete_temp("xajh/powerup");
		tell_object(me, "������齥����ƽϢ������\n");
	}
}
