inherit SKILL;

string *dodge_msg = ({
	"ֻ��$n��Хһ�����������ϱ�ֱ���������࣬�����$N��һ�С�\n",
	"ֻ��$n��������ת����ͬһ�����㣬ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
"$n��ȻŤ����������һ�������ض����$N�Ĺ��ơ�\n",
"$n����һ�����ɣ���������һ��ת�ۣ�$N������ȫ����ա�\n",
"$N��������$n����֪����ô$nͻȻ��ʧ��������$N�᷽��\n",
"$nͻȻ��������Ȱ����Ử�У�ٿ���������ɿ��⡣\n",
});

int valid_enable(string usage) 
{ 
	return (usage == "dodge") || (usage == "move"); 
}

int valid_learn(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp;

	if ((int)me->query_skill("shexing-lifan", 1) < 100 || ! living(me))
		return;

	ap = ob->query_skill("force") + ob->query_skill("never-defeated", 1)/3;
	dp = me->query_skill("dodge");

	if (random(ap*4) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(4))
		{
		case 0:
		case 1:
		default:
			result += (["msg" : HIM "����$n" HIM "��Ȼ����һ�䣬����������Ӱ��$N"
					    HIM "һʱ�����й���ȫ�����˿մ���"NOR"\n"]);
			break;
		}
		return result;
	} else
	{
		switch (random(4))
		{
		case 0:
		case 1:
		default:
			result = HIY "ֻ��$n" HIY "΢΢һЦ����������ζ���"
				 "��ʱ������������$n" HIY "�Ļ�Ӱ������$N"
				 HIY "��Ϊ��������������ʵ������������"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

string perform_action_file(string action)
{
	return __DIR__"shexing-lifan/" + action;
}
int practice_skill(object me)
{
	return notify_fail("������ֻ��ͨ���о�����ߡ�\n");
}

