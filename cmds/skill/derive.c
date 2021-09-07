// derive.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

varargs int deriving(object me);
int halt_deriving(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object where;
	int point;
	string skill;

	seteuid(getuid());
	where = environment(me);
	
	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (me->is_busy() || me->query_temp("pending/deriving"))
		return notify_fail("��������æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("ս���л��Ǻúõ�����Եаɡ�\n");

	if (me->query("combat_exp") < 100000)
		return notify_fail("���ʵս����̫ǳ�����޷����ͨ��ʵս��õ��ĵá�\n");

	if (me->query("experience") < me->query("learned_experience") + 100)
		return notify_fail("�����ڻ��۵�ʵս��ỹ̫�١�\n");

	if (me->query("qi") < me->query("max_qi") * 7 / 10)
		return notify_fail("������û�г����������������ʵս���ĵá�\n");

	if ((int)me->query("jing") * 100 / (int)me->query("max_jing") < 70)
		return notify_fail("�����ھ��񲻼ã�����ץסʵս����е���Ҫ��\n");

	//if (environment(me)->query("no_fight"))
	//	return notify_fail("���޷�������ط���������ͨ��ʵս�õ����ĵá�\n");

	if (arg && sscanf(arg, "%d %s", point, skill) == 2 ||
	    arg && sscanf(arg, "%d", point) == 1)
	{
		if (me->query("experience") - me->query("learned_experience") < point)
			return notify_fail("�㲢û�л�����ô��ʵս��ᡣ\n");

		if (point < 100)
			return notify_fail("�ƺ�û�б�ҪΪ�����������¹���\n");
	} else
	{
		point = -1;
		if (arg)
			sscanf(arg, "%s", skill);
	}

	if (me->query("id") == "dongfangming")
		tell_object(me, "skill = " + skill + ".\n"
				"point = " + point + ".\n");

	if (! stringp(skill)) skill = "martial-cognize";

	write("��ĬĬ����������ǰһ��ʱ��Ͷ��ֽ���ʱ�����Σ���ʼ���ռ�ȡ���е��ĵá�\n");

	me->set_temp("pending/deriving", 1);
	me->set_temp("derived_point", point);
	me->set_temp("derived_skill", skill);

	me->set_short_desc("����������ʽ��");
	message_vision("$N�����ſ����ƣ���ǰ���������㵸���ƺ���˼��ʲô��\n", me);
	
	me->start_busy(bind((:call_other, __FILE__, "deriving" :), me),
		       bind((:call_other, __FILE__, "halt_deriving" :), me));

	return 1;
}

varargs int deriving(object me)
{
	int improve;
	int cost;
	string skl_id, skl_name;
	object weapon;
	string skill;
	
	skill = me->query_temp("derived_skill");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "sword" ||
	    skill != "sword-cognize")
		skl_id = "martial-cognize";
	else skl_id = "sword-cognize";

	skl_name = to_chinese(skl_id);

	if (! me->can_improve_skill(skl_id))
	{
		write("��о��Լ���ʵս���黹��Ƿȱ�����޷�"
		      "�����߾����" + skl_name + "��\n");
		message("vision", me->name() + "�����̾�˿���������"
			"�ķ���һ����Ĵ���\n", environment(me), ({ me }));
		me->delete_temp("pending/deriving");
		me->set_short_desc(0);
		return 0;
	}

	cost = me->query_skill(skl_id, 1) / 2 + 100;//ԭ����cost�Ǽ��ܵȼ�����10�����ǳ���4,2017.7.6�ٴ�������ȡЧ��
	if (cost + me->query("learned_experience") > me->query("experience"))
		cost = me->query("experience") - me->query("learned_experience");

	// gain martial-cognize & combat_exp, potential
	improve = cost * (1 + random(10 + me->query_skill(skl_id, 1) / 8));
	if (me->can_improve_skill(skl_id))
		me->improve_skill(skl_id, improve);

	me->add("combat_exp", 1 + random(2));

	if (random(2))
		// not limit by potential limit
		me->add("potential", 1);

	// cost experience
	if (me->add("learned_experience", cost) >= me->query("experience"))
	{
		write("�㽫ʵս�л�õ�����ĵó�ֵ����������ˡ�\n");
		message("vision", me->name() + "΢΢һЦ������������Ϊϲ�á�\n",
			environment(me), ({ me }));
		me->delete_temp("pending/deriving");
		me->delete_temp("derived_point");
		me->delete_temp("derived_skill");
		me->set_short_desc(0);
		return 0;
	}

	if (me->query_temp("derived_point") > 0)
	{
		if (me->add_temp("derived_point", -cost) < 1)
		{
			write("������������һЩʵս�л�õ�����ĵá�\n");
			message("vision", me->name() + "΢΢һЦ������������Ϊϲ�á�\n",
				environment(me), ({ me }));
			me->delete_temp("pending/deriving");
			me->delete_temp("derived_point");
			me->delete_temp("derived_skill");
			me->set_short_desc(0);
			return 0;
		}
	}

	switch (skl_name)
	{
	case "��ѧ����":
		switch (random(20))
		{
		case 0:
			write("����˼���ã����ڹ������������µ���ᡣ\n");
			break;
	
		case 1:
			write("��ĬĬ˼������ȭ�Ź�������ͨ��һЩ�ؽڡ�\n");
			break;
	
		case 2:
			write("�㾲����ĥ����������������һ����⡣\n");
			break;
	
		case 3:
			write("���ܽ��˼�ʶ�������ֱ�����������ͨ�����е�һЩ���ء�\n");
			break;
		}
		break;

	case "��������":
		switch (random(20))
		{
		case 0:
			write("����ӳ�����ϸϸ��Ħ������΢֮����\n");
			break;
	
		case 1:
			write("�����г�����Ĩ�������������������ַ��Ĳ�ͬ��\n");
			break;
	
		case 2:
			write("�㾲����ĥ���·���������һ�㽣���Ϲ��ؽ��˵ļ��ɡ�\n");
			break;
	
		case 3:
			write("����ǰ���ֳ���ͬ���ɵĸ�ʽ��������������\n");
			break;
		}
		break;
	}

	if (random(15) == 0 && me->query("total_hatred") > 0)
	{
		me->add("total_hatred", -(random(4) + 1));
		tell_object(me, CYN "��ֻ��һ������͸��θ�������ɱ�⽥����"NOR"\n");
		if (me->query("total_hatred") < 0)
			me->set("total_hatred", 0);
	}

	return 1;
}

int halt_deriving(object me)
{
	tell_object(me, "��������ת���ջ���ͷ������˼����ѧ�ذ¡�\n");
	tell_room(environment(me), me->name() + "Ψһ��ü����ס�����ơ�\n", me);
	me->delete_temp("pending/deriving");
	me->delete_temp("derived_point");
	me->delete_temp("derived_skill");
	me->set_short_desc(0);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : derive [<����>] [ ���� ]

    ���ָ������������ռ�ȡʵս�е���ᣬ�����ֵ����������е��ذ��Ժ󣬿��������Լ�����ѧ������
����һ�ż����ѧ�ʣ���������ѧ�Ļ�������Ϊһ����ʦ����ѧ�����Ǳز����ٵġ�
�����װ���˽���������������ָ���˼�����Ϊ sword-cognize���򽫻�ý���������

HELP );
	return 1;
}

