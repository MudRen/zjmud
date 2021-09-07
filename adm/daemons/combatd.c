// combatd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_DBASE;

// �����������(/combat/)��˵��
// PKS��ɱ���������Ŀ
// MKS��ɱ����NPC��Ŀ(���ﲻ����)
// WPK������ɱ����ҵĴ���
// WPK_NOTGOOD������ɱ��������(shen < 500)��ҵĴ���
// WPK_BAD��    ����ɱ����а��(shen <-500)��ҵĴ���
// WPK_NOTBAD�� ����ɱ����а��(shen >-500)��ҵĴ���
// WPK_GOOD��   ����ɱ��������(shen > 500)��ҵĴ���
// DPS������������ҵĴ���
// DPS_NOTGOOD���������η�����(shen < 500)��ҵĴ���
// DPS_BAD��    �������ε�а��(shen <-500)��ҵĴ���
// DPS_NOTBAD�� �������η�а��(shen >-500)��ҵĴ���
// DPS_GOOD��   �������ε�����(shen > 500)��ҵĴ���
// dietimes��   �����Ĵ���

// combat/today��¼(mapping)
// which_day: ����(ʵ��ʱ��������)
// id       : n, ��������ĳ��ID�Ĵ���

#define DEFAULT_MAX_PK_PERDAY	   3
#define DEFAULT_MAX_PK_PERMAN	   1

// �������(random(my_exp) > EXP_LIMIT���򲻼Ӿ���)
#define	EXP_LIMIT	20000000
string *guard_msg = ({
	append_color(CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�"NOR"\n", CYN),
	append_color(CYN "$N������$n��һ��һ������ʱ׼���������ơ�"NOR"\n", CYN),
	append_color(CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������"NOR"\n", CYN),
	append_color(CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����"NOR"\n", CYN),
	append_color(CYN "$N�������ƶ����Ų����Ż����֡�"NOR"\n", CYN),
});

string *catch_hunt_msg = ({
	append_color(HIW "$N��$n������������ۺ죬���̴���������"NOR"\n", HIW),
	append_color(HIW "$N����$n��ȣ����ɶ������㣡��"NOR"\n", HIW),
	append_color(HIW "$N��$nһ���棬������˵�ʹ���������"NOR"\n", HIW),
	append_color(HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����"NOR"\n", HIW),
	append_color(HIW "$Nһ����$n�����һ㶣���У����������㣡��"NOR"\n", HIW),
	append_color(HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���"NOR"\n", HIW),
	append_color(HIW "$N�ȵ�����$n�����У���"NOR"\n", HIW) });

string *winner_msg = ({
	append_color(CYN "\n$N������Ц��˵���������ˣ�"NOR"\n", CYN),
	append_color(CYN "\n$N˫��һ����Ц��˵�������ã�"NOR"\n", CYN),
	append_color(CYN "\n$Nʤ�����У����Ծ�����ߣ�Ц�������ã�"NOR"\n", CYN),
	append_color(CYN "\n$N˫��һ����Ц��˵����֪���ҵ������˰ɣ�"NOR"\n", CYN),
	append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ��»ؿ�����ô��ʰ�㣡"NOR"\n", CYN),
	append_color(CYN "\n$n���һ�ݣ��޺޵�˵�������ӱ���ʮ�겻��"NOR"\n", CYN),
	append_color(CYN "\n$n��ɫһ����˵�����������ˣ��͵���������ɣ�"NOR"\n", CYN),
	append_color(CYN "\n$n������Ц���е������������ã��������ã���һ���������������"NOR"\n", CYN),
	append_color(CYN "\n$n��ɫ΢�䣬˵��������������"NOR"\n", CYN),
	append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ�����������"NOR"\n", CYN),
	append_color(CYN "\n$n���һ�ݣ�������Ҿ˵�����������ղ�������Ȼ������"NOR"\n", CYN),
});

void create()
{
	int pd, pm;

	seteuid(getuid());
	set("channel_id", "ս������");

	if (undefinedp(pd = CONFIG_D->query_int("max pk perday")))
		pd = DEFAULT_MAX_PK_PERDAY;

	if (undefinedp(pm = CONFIG_D->query_int("max pk perman")))
		pm = DEFAULT_MAX_PK_PERMAN;

	set("pk_perday", pd);
	set("pk_perman", pm);
}

// message after damage info
static string foo_before_hit = 0;
static string foo_after_hit = 0;

void set_bhinfo(string msg)
{
	if (! foo_before_hit)
	{
		foo_before_hit = msg;
		return;
	}

	foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
	if (! foo_after_hit)
	{
		foo_after_hit = msg;
		return;
	}

	foo_after_hit += msg;
}

string query_bhinfo() { return foo_before_hit; }

string query_ahinfo() { return foo_after_hit; }

void clear_bhinfo() { foo_before_hit = 0; }

void clear_ahinfo() { foo_after_hit = 0; }

string damage_msg(int damage, string type)
{
	string str;
	if (damage == 0)
		return "���û������κ��˺���\n";   
	switch (type)
	{
	case "����":
	case "����":
		if (damage < 15)  str = "���ֻ������ػ���$p��Ƥ�⡣"; else
		if (damage < 40)  str = "�����$p$l����һ��ϸ����Ѫ�ۡ�"; else
		if (damage < 100) str = "������͡���һ������һ���˿ڣ�"; else
		if (damage < 200) str = "������͡���һ������һ��Ѫ���ܵ��˿ڣ�"; else
		if (damage < 400) str = "������͡���һ������һ���ֳ�������˿ڣ�����$N������Ѫ��"; else
				  str = "���ֻ����$nһ���Һ���$w����$p$l����һ������ǵ��˿ڣ���";
		  return str  +"\n";
		break;
	case "����":
		if (damage < 15)  str = "���ֻ������ش���$p��Ƥ�⡣"; else
		if (damage < 40)  str = "�����$p$l�̳�һ�����ڡ�"; else
		if (damage < 100) str = "������ۡ���һ��������$n$l����"; else
		if (damage < 200) str = "������ۡ���һ������̽�$n��$l��"; else
		if (damage < 400) str = "��������͡���һ����$w����$p$l�̳�һ��Ѫ������"; else
				  str = "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ���";
		 return str  +"\n";
		break;
	case "����":
	case "����":
		if (damage < 15)  str = "���ֻ����������������Ĳ�Ӭ��΢���˵㡣"; else
		if (damage < 40)  str = "�����$p��$l���һ�����ࡣ"; else
		if (damage < 100) str = "���һ�����У�$n��$l��ʱ����һ���ϸߣ�"; else
		if (damage < 150) str = "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���"; else
		if (damage < 200) str = "������项��һ����$n����������"; else
		if (damage < 400) str = "�����һ�¡��项��һ�������$n��һ��ˤ���ڵأ�"; else
		if (damage < 800) str = "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��"; else
				  str = "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ����";
		 return str +"\n";
		break;
	case "����":
		if (damage < 15)  str = "���ֻ�ǰ�$n������˰벽����������"; else
		if (damage < 40)  str = "���$nʹ��һ������$p��$l���һ�����ˡ�"; else
		if (damage < 100) str = "���һ�����У���$n���ʹ��������ȥ��"; else
		if (damage < 150) str = "���$n�ƺ���һ��������һ����һ��ף���Ȼ���˵����ˣ�"; else
		if (damage < 200) str = "���$n�ƺ���һ������ɫһ�±�òҰף���Ȼ���˲��ᣡ"; else
		if (damage < 400) str = "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��"; else
		if (damage < 800) str = "������䡹��һ����$nȫ����Ѫ������������Ѫ���������"; else
				  str = "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ����";
		  return str +"\n";
		break;
	case "��Ѩ":
		if (damage < 15)  str = "���ֻ�����������$n��$l������û�е㵽Ѩ����"; else
		if (damage < 40)  str = "���$nʹ��һ������$p��$l���һ�����ࡣ"; else
		if (damage < 100) str = "���һ�����У�$N������$n$l�ϵ�Ѩ����$nֻ��һ����ľ��"; else
		if (damage < 200) str = "���$n�ƺ���һ��������һ����һ��ף���ʱ����$l��ľ��"; else
		if (damage < 400) str = "���$n��ɫһ�±�òҰף���$N����$l��Ѩ��,һ����ʹ�鲼����$l��"; else
		if (damage < 800) str = "���$nһ����У�$l��Ѩ��������,��ʹֱ���ķΣ�"; else
				  str = "���ֻ����$nһ���ҽУ�һ���ʹ�α�ȫ������ֱͦͦ�ĵ�����ȥ��";
		  return str +"\n";
		break;
	case "����":
		if (damage < 15)  str = "���ֻ����$n��Ƥ����������������ֻ���Ƶ�Ƥ��"; else
		if (damage < 40)  str = "�����$n$l���һ����΢���Ϻۡ�"; else
		if (damage < 100) str = "�����ž����һ����$n$l���һ��������Ѫ�ۣ�"; else
		if (damage < 200) str = "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�"; else
		if (damage < 400) str = "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�"; else
		if (damage < 800) str = "�����ž����һ�����죡��һ�º�������ֻ���$nƤ��������Ѫ���ɽ���"; else
				  str = "���ֻ����$nһ���Һ���$w���صس�����$p��$l��$n��ʱѪ���ɣ�";
		  return str +"\n";
		break;
	case "������":
		if (damage < 15)  str = "���$N�ܵ�$n�����������ƺ�һ����"; else
		if (damage < 40)  str = "���$N��$n�ķ������Ѫ���ڣ���ʧɫ��"; else
		if (damage < 100) str = "���$N��$n�ķ����վ�����ȣ�ҡҡ�λΡ�"; else
		if (damage < 200) str = "���$N��$n���������𣬡��١���һ������һ����"; else
		if (damage < 300) str = "���$N��$n����÷���������������ð����顣"; else
		if (damage < 400) str = "���$N��$n�����������ؿ������ܵ�һ���ػ������͸��������"; else
		if (damage < 600) str = "���$N��$n����������ǰһ�ڣ�����ι�ȥ����"; else
				  str = "���$N��$n�������𣬿�����Ѫ������������ߵķ��������ȥ����";
		   return str +"\n";
		break;
	case "����":
		if (damage < 10)  str = "���ֻ����������������Ǹ�$nɦ��һ������"; else
		if (damage < 40)  str = "�����$n��$l�ҳ�һ��С������"; else
		if (damage < 100) str = "���$N��һ���Ҹ����ţ�$n��$l��ʱ����һ���ϸߣ�"; else
		if (damage < 150) str = "���$N��һ���Ҹ����ţ�$n�ƺ�һ����Ȼ���˲�С�Ŀ���"; else
		if (damage < 200) str = "���ֻ�����项��һ����$n�۵�����������������"; else
		if (damage < 400) str = "�����һ�¡��䡹��һ���ҵ�$n��ð���ǣ���һ��ˤ����"; else
		if (damage < 800) str = "������ص����У�$n��ǰһ�ڣ����ۡ���һ���³�һ����Ѫ��"; else
				  str = "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã�";
		   return str +"\n";
		break;
	default:
		if (! type) type = "�˺�";
		if (damage < 50)  str = "���ֻ����ǿ���һ����΢"; else
		if (damage < 100)  str = "��������΢��"; else
		if (damage < 200) str = "������һ��"; else
		if (damage < 300) str = "���һ������"; else
		if (damage < 500) str = "��������Ϊ���ص�"; else
		if (damage < 700) str = "�������൱���ص�"; else
		if (damage < 900) str = "������ʮ�����ص�"; else
		if (damage < 1000) str = "�����ɼ������ص�"; else
				  str = "�����ɷǳ����µ�����";
		return  str+ type  +"��\n";
	}
}

string eff_status_msg(int ratio)
{
	if (ratio==100) return HIG "��������Ѫ��ӯ����û�����ˡ�" NOR;
	if (ratio > 90) return HIG "�ƺ����˵����ˣ��������������������" NOR;
	if (ratio > 80) return HIY "�������������˵����ˡ�" NOR;
	if (ratio > 70) return HIY "���˼����ˣ������ƺ��������¡�" NOR;
	if (ratio > 60) return HIY "���˲��ᣬ������״������̫�á�" NOR;
	if (ratio > 50) return HIR "��Ϣ���أ�������ʼɢ�ң��������ܵ�����ʵ���ᡣ" NOR;
	if (ratio > 40) return HIR "�Ѿ��˺����ۣ���������֧����������ȥ��" NOR;
	if (ratio > 30) return HIR "�����൱�ص��ˣ�ֻ�»�������Σ�ա�" NOR;
	if (ratio > 20) return RED "����֮���Ѿ�����֧�ţ��ۿ���Ҫ���ڵ��ϡ�" NOR;
	if (ratio > 10 ) return RED "ҡͷ���ԡ�����бб��վ��վ���ȣ��ۿ���Ҫ���ڵ��ϡ�" NOR;
	if (ratio > 5 )return RED "�Ѿ���������״̬����ʱ������ˤ����ȥ��" NOR;
	return RED "���˹��أ��Ѿ�����һϢ�����ڵ�Ϧ��" NOR;
}

int valid_power(int combat_exp)
{
	if (combat_exp < 2000000)
		return combat_exp / 1000;

	combat_exp -= 2000000;
	if (combat_exp < 1000000)
		return 2000 + combat_exp / 10000;

	combat_exp -= 1000000;
	return 2000 + (1000 / 10) + (combat_exp / 2000);
}

varargs int skill_power(object ob, string skill, int usage, int delta)
{
	int status, level, power;
	mapping dbase;
	mapping temp;
	mapping fight;
	mapping apply;

	if (! living(ob)) return 0;

	level = ob->query_skill(skill);

	dbase = ob->query_entire_dbase();
	temp = ob->query_entire_temp_dbase();
	if (temp)
	{
		apply = temp["apply"];
		fight = temp["fight"];
	}

	switch (usage)
	{
		case SKILL_USAGE_ATTACK:
			if (apply) level += apply["attack"];
			break;
		case SKILL_USAGE_DEFENSE:
			if (apply) level += apply["defense"];
			break;
	}

	level += delta;
	if (level < 1)
	{
		power = valid_power((int)ob->query("combat_exp")) / 2;
		if (usage == SKILL_USAGE_ATTACK)
			power = power / 30 * dbase["str"];
		else
			power = power / 30 * dbase["dex"];

	 	return  power;
	}

	if (level > 500)
		power = level * level / 10000 * level;
	else
		power = level * level * level / 10000;

	power += valid_power(dbase["combat_exp"]);

	if (usage == SKILL_USAGE_ATTACK)
	{
		power = power / 30 * (dbase["str"] + (temp ? temp["str"] : 0));
		if (fight && ob->is_fighting())
			 power += power / 100 * fight["attack"];
	} else
	{
		power = power / 30 * (dbase["dex"] + (temp ? temp["dex"] : 0));
		if (fight && ob->is_fighting())
			 power += power / 100 * fight[skill];
	}
	return power;
}

varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
	mapping my, your;
	mapping my_temp, your_temp;
	mapping prepare, action;
	string limb, *limbs;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
	string parry_msg;
	mixed foo;

	int crit,delta;
	int ap, dp, pp;
	int damage, damage_bonus, defense_factor;
	int wounded;
	int has_weapon;

	object weapon2;	// weapon of victim
	object cloth;   // armor of victim

	string skill_name,result;
	string damage_msg,damage_info;
	mapping fight;

	object env_me;
	object env_v;

	if (environment(me)->query("no_fight")&&!me->query_condition("killer")&&!victim->query_condition("killer"))
	{
		message_vision("$N��$n��������һ������ס���С�\n",me, victim);
		me->remove_enemy(victim);
		victim->remove_enemy(me);
		return 0;
	}

	if (environment(me) != environment(victim))
	{
		me->remove_enemy(victim);
		victim->remove_enemy(me);
		return 0;
	}

	my = me->query_entire_dbase();
	your = victim->query_entire_dbase();

	if (! (my_temp = me->query_entire_temp_dbase()))
		my_temp = allocate_mapping(5);

	if (! (your_temp = victim->query_entire_temp_dbase()))
		your_temp = allocate_mapping(5);

	//
	// (0) Choose skills.
	//
	prepare = me->query_skill_prepare();
	if (! prepare) prepare = ([]);

	if (objectp(weapon))
		attack_skill = weapon->query("skill_type");
	else
	{
		switch (sizeof(prepare))
		{
		case 0: attack_skill = "unarmed"; break;
		case 1: attack_skill = (keys(prepare))[0]; break;
		case 2: attack_skill = (keys(prepare))[me->query_temp("action_flag")]; break;
		}
	}

	if (attack_skill == "pin")
		attack_skill = "sword";

	// (1) Find out what action the offenser will take.
	//
	me->reset_action();
	action = me->query_action();

	has_weapon = weapon || me->query_temp("armor/hands");

	if (! action)
	{
		// reconfirm
		me->reset_action();
		action = me->query_action();
		if (! mapp(action))
		{
			CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s(%s): bad action = %O",me->query("name"), me->query("id"),me->query_action(1)));
			return 0;
		}
	}

	if (me->query_temp("action_flag") == 0)
		result = "\n" + action["action"] + "��\n";
	else
		result = "\n������" + action["action"] + "��\n"; 

	if(!stringp(skill_name = action["skill_name"]))
		if(!stringp(skill_name = me->query_skill_mapped(attack_skill)))
			skill_name = attack_skill;
	me->set_temp("attack_skill_name",to_chinese(skill_name));

	//
	// (2) Prepare AP, DP for checking if hit.
	//
	limbs = victim->query("limbs");
	if (! arrayp(limbs))
	{
		limbs = ({ "����" });
		victim->set("limbs", limbs);
	}
	limb = limbs[random(sizeof(limbs))];

	if (! my["not_living"])
	{
		fight = allocate_mapping(5);
		fight["attack"] = action["attack"];
		fight["dodge"]  = action["dodge"];
		fight["parry"]  = action["parry"];
		my_temp["fight"] = fight;
	}
	//���㹥���߼��� ������
	ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
	if (ap < 1) ap = 1;

	if (my["character"] == "���ռ�թ")
		//�����Ը�AP�ӳ�120%
		ap += ap * 20 / 100;     
	//���㱻 ������ �� �Ṧ ����ֵ
	dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
	if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
	{
		//���װ�������Ṧ������������Ṧ�ļӳ���
		dp += dp / 200 * SKILL_D(dodge_skill)->query_effect_dodge(me, victim);
	}
	if (dp < 1) dp = 1;
	//����������ߴ��ڷ�æ״̬������ֵ����3�� 
	if (victim->is_busy()) dp /= 3;

	//
	// (3) Fight!

	damage = 0;   //�ƻ�
	wounded = 0;   //����
	damage_info = "";  //�ƻ���Ϣ
	
	//������������ֵ+�������ߵĶ���ֵ��С�ڶ���ֵ����Ϊ�����ɹ�
	if (random(ap + dp) < dp && victim->query("qi")!=0)
	{  // Does the victim dodge this hit?

#if INSTALL_COMBAT_TEST
		if (wizardp(me) && me->query("env/combat_test"))
			tell_object(me, HIY "�����Ծ��顿������ AP��" + ap +"��DP��" + dp + "��"NOR"\n");
		if (wizardp(victim) && victim->query("env/combat_test"))
			tell_object(victim, HIC "�����Ծ��顿���Է� AP��" + ap + "��DP��" + dp + "��"NOR"\n");
#endif

		//���û��װ�������Ṧ���͸�������Ṧ
		if (! dodge_skill) dodge_skill = "dodge";
		//ȡ���Ṧ�Ķ�����Ϣ��
		result += SKILL_D(dodge_skill)->query_dodge_msg(limb);
		damage = -1;
		//�ж��Ƿ������Ṧ��������
		//�������ֵС�ڹ���ֵ�����һ�����˹���
		if (userp(me) || userp(victim))  
		{
			if (random(dp+ap) < dp && random(my["int"]) > 14)
			{
				//����漴�������ߵľ��鲻���ڼ��޾��飬�����������ͼӽ���
				if (your["combat_exp"] < EXP_LIMIT && victim->query("combat_exp")<me->query("combat_exp"))
				{
					tell_object(victim,"����"HIC"���"NOR+me->query("name")+"ʱ��"HIG"��"+to_chinese(dodge_skill)+"��"NOR"��������: "YEL"�书������ "HIY"��"NOR","YEL"ʵս���� "HIY"��" NOR"\n");				
					your["combat_exp"]++;
					victim->improve_skill(dodge_skill, 1);
			       
				}
			}
		}
	} 
	else  //����������ɹ������ж��Ƿ����ӹ����Ľ���
	{
		//
		//      (4) Check if the victim can parry this attack.
		// ���ǿ��Ի�����
		if (userp(me) || userp(victim))     
		{
			//�����Ƿ���蹥��������
			//�������С�ڶ��� ���� ������Դ���14 ������Ǳ���Ƿ񳬳�
			if (random(ap + dp) < dp && random(my["int"]) > 12 )
			{
				if( me->query("combat_exp") < victim->query("combat_exp"))
				{
					if(me->query("potential") < me->query_potential_limit())
					{
						tell_object(me,"����"HIR"����"NOR+victim->query("name")+"ʱ��"HIG"��"+to_chinese(attack_skill)+"��"NOR"��������:"YEL" �书������ "HIY"��"NOR","YEL"����� "HIY"��" NOR"\n");
						my["potential"]++;
						your_temp["give_potential"] += my["mud_age"] / 86400;
						me->improve_skill(attack_skill, 1);     
					}
				}
			}
		}
		delta = 0;
		//ȡ��װ�����ֵı�������
		if (weapon2 = your_temp["weapon"])
		{
			if (! weapon) delta = 10;  //���û�б�����delta=10
		} 
		else
		{
			if (weapon) delta = -10;   //��װ��������delta=-10
		}
		//���㱻������ �мܼ��� ��ֵ
		pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
		//����������� ��æ���м�ֵ����3��
		if (victim->is_busy()) pp /= 3;
		if (pp < 1) pp = 1;
		//���������мܼ��ܸ�����м�ֵ�ӳˡ�
		if (stringp(parry_skill = victim->query_skill_mapped("parry")))
			pp += pp / 200 * SKILL_D(parry_skill)->query_effect_parry(me, victim);
		//������������ֵ+�м�ֵ��С���м�ֵ ���ж� �мܳɹ���������ѪΪ0
		if (random(ap + pp) < pp && victim->query("qi")!=0)
		{
		       
#if INSTALL_COMBAT_TEST
			if (wizardp(me) && me->query("env/combat_test"))
				tell_object(me, HIY "�����Ծ��顿������ AP��" + ap + "��PP��" + pp + "��"NOR"\n");
			if (wizardp(victim) && victim->query("env/combat_test"))
				tell_object(victim, HIC "�����Ծ��顿���Է� AP��" + ap + "��PP��" + pp + "��"NOR"\n");
#endif
			//���û�������мܣ������ [�����м�]
			if (! parry_skill) parry_skill = "parry";
			// change to SKILL_D(parry_skill) after added parry msg to those
			// martial arts that can parry.
			//ȡ���д�������[�����м�]��Ϣ
			parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);
			//���û��[�����м�]�������м���Ϣ
			if (! stringp(parry_msg))
				//��ȡ��[�����м�]������Ϣ
				parry_msg = SKILL_D("parry")->query_parry_msg(weapon2);
			//������м���Ϣ������result+�м���Ϣ
			if (stringp(parry_msg))
				result += parry_msg;
			damage = -2;
			//�ж��Ƿ�����мܽ���
			//����м�ֵС�ڹ��������мܳɹ������Ҽ��� xx>30
		      if (userp(me) || userp(victim))  
		      {
				if (random(ap + pp) < pp && random(my["int"]) > 14)
				{
					//���ϣ�ͨ���͸����мܽ���
					if (your["combat_exp"] < EXP_LIMIT && victim->query("combat_exp")<me->query("combat_exp"))
					{
						tell_object(victim,"����"HIM"�м�"NOR+me->query("name")+"ʱ��"HIG"��"+to_chinese(parry_skill)+"��"NOR"��������:"YEL" �书������ "HIY"��"NOR","YEL"����� "HIY"��" NOR"\n");					
						your["combat_exp"]++;		   
						victim->improve_skill(parry_skill, 1);
					}
					else
					{
					     tell_object(victim,WHT+"����Ķ���̫���ˣ��޷�ȡ���κξ��飡������"NOR"\n");
					}
				}
		      }
		} 
		else
		{
			//
			// (5) We hit the victim and the victim failed to parry
			//
			//����б�������ȡ�������Ĺ�����������ȡ�����ֹ�����
			if (weapon)
				damage = me->query_temp("apply/damage");
			else
				damage = me->query_temp("apply/unarmed_damage");
			//�������������һ���������Χ������
			damage = (damage + random(damage)) / 2;
			if (action["damage"])
				damage += action["damage"] * damage / 100;
			//����������ȡ��
			damage_bonus = me->query_str();
			//�ж��Ƿ��� ��ŭ״̬
			if (my["jianu"])
			{
				// does angry bnous
				damage_bonus += me->cost_craze(my["jianu"]);
				//�Ƿ�Ϊ��״̬�������״̬��Ϣ
				if (me->query_craze() > 1000 && random(my["jianu"] + 200) > 200)
				{
					damage_info += random(2) ? HIR "$N" HIR "���һ����˫ĿԲ����һ��������ɱ����Ȼ����"NOR"\n"
								 : HIR "$N" HIR "�ܲ����������ǰ�������н���$n" HIR "���������顣"NOR"\n";
					//����ŭ��ֵ
					me->cost_craze(200 + random(300));
					damage_bonus += my["jianu"] * 2;
				}
			}

			// Clear the special message info after damage info
			foo_before_hit = 0;
			foo_after_hit = 0;

			// Let force skill take effect.
			if (my["jiali"] && (my["neili"] > my["jiali"]))
			{
				if (force_skill = me->query_skill_mapped("force"))
				{
					foo = SKILL_D(force_skill)->force_hit_ob(me, victim, damage_bonus, my["jiali"]);
					if (stringp(foo)) damage_info += foo; else
					if (intp(foo)) damage_bonus += foo; else
					if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage_bonus += foo["damage"];
					}
				}

#if INSTALL_COMBAT_TEST
				if (wizardp(me) && me->query("env/combat_test"))
					tell_object(me, HIY "�����Ծ��顿������ AP��" + ap + "��DP��" + dp + "��PP��" + pp +
						    "���˺�Ч����" + damage + "�������˺�Ч����" + damage_bonus + "��"NOR"\n");
				if (wizardp(victim) && victim->query("env/combat_test"))
					tell_object(victim, HIC "�����Ծ��顿���Է� AP��" + ap + "��DP��" + dp + "��PP��" + pp +
						    "���˺�Ч����" + damage + "�������˺�Ч����" + damage_bonus + "��"NOR"\n");
#endif
			}

			if (action["force"])
				damage_bonus += action["force"] * damage_bonus / 100;

			// calculate the damage
			if (damage_bonus > 0)
				damage += (damage_bonus + random(damage_bonus)) / 3;

			// Let's attack & parry skill, weapon & armor do effect
			while (damage > 0)
			{
				if (my["not_living"] || your["not_living"])
					// Only two living do this
					break;

				if (damage < 1) break;

				// Let parry skill take its special effort.
				if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
				{
					victim->set_temp("dodge_valid_damage", 1);
					foo = SKILL_D(dodge_skill)->valid_damage(me, victim, damage, weapon);
					victim->delete_temp("dodge_valid_damage");
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
					if (damage < 1) break;
				}

				if (stringp(parry_skill = victim->query_skill_mapped("parry")))
				{
					foo = SKILL_D(parry_skill)->valid_damage(me, victim, damage, weapon);
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
					if (damage < 1) break;
				}
				// ħ����
				if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["beast"]))
				{
					foo = cloth->valid_damage(me, victim, damage, weapon);
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
				}
				else if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["armor"]))
				{
					foo = cloth->valid_damage(me, victim, damage, weapon);
					if (stringp(foo)) damage_info += foo; else
					if (intp(foo)) damage += foo; else
					if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
				}
				else if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["cloth"]))
				{
					foo = cloth->valid_damage(me, victim, damage, weapon);
					if (stringp(foo)) damage_info += foo; else
					if (intp(foo)) damage += foo; else
					if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
				}

				if (damage < 1) break;

				if (martial_skill = me->query_skill_mapped(attack_skill))
				{
					foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
					if (damage < 1) break;
				}

				// Let weapon or living have their special damage.
				if (weapon)
				{
					foo = weapon->hit_ob(me, victim, damage);
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
				}
				else
				{
					foo = me->hit_ob(me, victim, damage);
					if (stringp(foo))
						damage_info += foo;
					else if (intp(foo))
						damage += foo;
					else if (mapp(foo))
					{
						damage_info += foo["msg"];
						damage += foo["damage"];
					}
				}
				break;
			}

			//
			//      (6) Inflict the damage.
			//
			if (damage > 0)
			{
				if (my["character"] == "�ĺ�����")
					damage += damage * 20 / 100;

				wounded = damage;

				if (wounded > 400)
					wounded = (wounded - 400) / 4 + 300;
				else if (wounded > 200)
					wounded = (wounded - 200) / 2 + 200;
				else if (wounded < 1)
					wounded = 0;

				// recalculate damage
				if (damage > 400)
					damage = (damage - 400) / 4 + 300;
				else if (damage > 200)
					damage = (damage - 200) / 2 + 200;

				if (your["character"] == "��������")
					wounded -= wounded * 20 / 100;

				damage = COMBAT_D->calc_damage(me, victim, damage);
//��������
				if( (crit = me->query("gain/2ap") - victim->query("gain/2dp")) > 0 )
				{
					if( crit > random(150) )
					{
						damage *= 2;
						//wounded *= 2;
						result += RED"$N�����ע������$n��������һ����"NOR"\n";
					}
				}
				damage = victim->receive_damage("qi", damage, me);
				if (wounded > 0 && (has_weapon || random(3) == 1))
				{
					wounded = COMBAT_D->calc_wound(me, victim, wounded);
					victim->receive_wound("qi", wounded, me);
				}

#if INSTALL_COMBAT_TEST
				if (wizardp(me) && me->query("env/combat_test"))
					tell_object(me, HIY "�����Ծ��顿�����" + victim->query("name") + "���" + damage + "���˺���" +  wounded + "�㴴�ˡ�"NOR"\n");
				if (wizardp(victim) && victim->query("env/combat_test"))
					tell_object(victim, HIG "�����Ծ��顿�����ܵ�" + me->query("name") + damage + "���˺���" + wounded + "�㴴�ˡ�"NOR"\n");
#endif

				// add message before hit in victim
				if (foo_before_hit)
					result += foo_before_hit;

				result += damage_msg(damage, action["damage_type"]);
				damage_info += "( $n" + eff_status_msg(victim->query("qi") * 100 / victim->query("max_qi")) + ")\n";
			}

			if (foo_after_hit)
				damage_info += foo_after_hit;
		}
	} 

	result = replace_string(result, "$l", limb);
	if (objectp(weapon))
		result = replace_string(result, "$w", weapon->name());
	else if (stringp(action["weapon"]))
		result = replace_string(result, "$w", action["weapon"]);
	else if (attack_skill == "finger" || attack_skill == "hand")
		result = replace_string(result, "$w", "��ָ" );
	else if (attack_skill == "strike" || attack_skill == "claw")
		result = replace_string(result, "$w", "����" );
	else
		result = replace_string(result, "$w", "ȭͷ" );

	message_combatd(result, me, victim, damage_info,damage,action["damage_type"]);

	if (damage > 0)
	{
		if (victim->is_busy())
			victim->interrupt_me(victim, 2 + random(2));
		if ((!me->query_temp("fight_team")) && (! me->is_killing(your["id"])) && (! victim->is_killing(my["id"])) 
			&& ! victim->query("not_living") && your["qi"] * 3 <= your["max_qi"])
		{
			me->remove_enemy(victim);
			victim->remove_enemy(me);
			if (me->query("can_speak") && victim->query("can_speak"))
				message_vision(winner_msg[random(sizeof(winner_msg))],me, victim);
			if (me == victim->query_competitor())
			{
				me->win();
				victim->lost();
			}
		}
	}

	if (functionp(action["post_action"]))
		evaluate(action["post_action"], me, victim, weapon, damage);

	if (attack_type == TYPE_REGULAR && damage < 1 && your_temp["guarding"])
	{
		if (random(my["dex"]) < 8)
		{
			message_vision("$Nһ�����У�¶����������\n",me,victim);
			do_attack(victim, me, your_temp["weapon"],TYPE_QUICK);
		} else
		{
			message_vision("$n��$N����ʧ�󣬳û�����������\n",me,victim);
			do_attack(victim, me, your_temp["weapon"],TYPE_RIPOSTE);
		}
	}
}

varargs string do_damage(object me, object target, mixed type, int damage, int percent, mixed final)
{
	mapping my;
	object weapon;
	object cloth;
	int apply;
	int armor;
	int wound;
	int jiali;
	int bonus;
	mixed foo;
	string msg;
	string skill;
	string *limbs;
	string limb;
	string damage_type;
	string result;
	int str;
	int damage_bonus;

	// Am I use weapon
	if (type == WEAPON_ATTACK)
	{
		apply  = me->query_temp("apply/damage");
		weapon = me->query_temp("weapon");
	}
	else if (type == UNARMED_ATTACK)
	{
		apply  = me->query_temp("apply/unarmed_damage");
		weapon = 0;
	}
	else
	{
		apply  = 0;
		weapon = 0;
	}

	// Check the target's armor
	armor = target->query_temp("apply/armor");

	damage += apply;
	msg = "";
	foo_after_hit = 0;

	while (type == UNARMED_ATTACK || type == WEAPON_ATTACK)
	{
		if (random(100) < 40)
			break;
		// Let parry skill take its special effort
		if (skill = target->query_skill_mapped("parry"))
		{
			foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
			if (stringp(foo))
				msg += foo;
			else if (intp(foo))
				damage += foo;
			else if (mapp(foo))
			{
				msg += foo["msg"];
				damage += foo["damage"];
			}
		}
		if (damage < 1) break;

		// Let dodge skill take its special effort
		if (skill = target->query_skill_mapped("dodge"))
		{
			target->set_temp("dodge_valid_damage", 1);
			foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
			target->delete_temp("dodge_valid_damage", 1);
			if (stringp(foo))
				msg += foo;
			else if (intp(foo))
				damage += foo;
			else if (mapp(foo))
			{
				msg += foo["msg"];
				damage += foo["damage"];
			}
		}

		if (damage < 1) break;
		  //ħ����
		if (cloth = target->query_temp("armor/beast"))
		{
			foo = cloth->valid_damage(me, target, damage, weapon);
			if (stringp(foo))
				msg += foo;
			else if (intp(foo))
				damage += foo;
			else if (mapp(foo))
			{
				msg += foo["msg"];
				damage += foo["damage"];
			}
		} else 
		// Let cloth & armor take its special effort
		if (cloth = target->query_temp("armor/armor"))
		{
			foo = cloth->valid_damage(me, target, damage, weapon);
			if (stringp(foo))
				msg += foo;
			else if (intp(foo))
				damage += foo;
			else if (mapp(foo))
			{
				msg += foo["msg"];
				damage += foo["damage"];
			}
		}
		else if (cloth = target->query_temp("armor/cloth"))
		{
			foo = cloth->valid_damage(me, target, damage, weapon);
			if (stringp(foo))
				msg += foo;
			else if (intp(foo))
				damage += foo;
			else if (mapp(foo))
			{
				msg += foo["msg"];
				damage += foo["damage"];
			}
		}
		break;
	}

	while (damage > 0)
	{
		if (target->is_busy()) target->interrupt_me(target, 4 + random(4));

		if (type == WEAPON_ATTACK)
			foo = weapon->hit_ob(me, target, damage);
		else if (type == UNARMED_ATTACK)
			foo = me->hit_ob(me, target, damage);
		else if (objectp(type))
			foo = type->hit_ob(me, target, damage);

		if (stringp(foo))	msg += foo;
		else if (intp(foo)) damage += foo;
		else if (mapp(foo))
		{
			msg += foo["msg"];
			damage += foo["damage"];
		}

		my = me->query_entire_dbase();
		if ((jiali = my["jiali"]) > 0 && my["neili"] >= jiali)
		{
			my["neili"] -= jiali;
			if (type == REMOTE_ATTACK)
			{
				damage_bonus = jiali * damage / 200;
			}
			else
			{
				damage_bonus = jiali * damage / 300;
				skill = target->query_skill_mapped("force");
				if (stringp(skill))
				{
					foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);

					if (stringp(foo)) msg += foo;
					else if (intp(foo)) damage_bonus += foo;
					else if (mapp(foo))
					{
						msg += foo["msg"];
						damage_bonus += foo["damage"];
					}
				}
				damage += damage_bonus;
			}
		}

		str = me->query_str() + me->query_temp("str");

		if (str < 20) damage += damage * str / 50;
		else if (str < 40) damage += damage * ((str - 20) / 2 + 20) / 50;
		else damage += damage * ((str - 40) / 4 + 30) / 50;

		if (damage < 1) break;

		if (damage > 1500)	damage = (damage - 1500) / 4 + 1000;
		else if (damage > 500)	damage = (damage - 500) / 2 + 500;

		damage = COMBAT_D->calc_damage(me, target, damage);
		target->receive_damage("qi", damage, me);
		wound = (damage - random(armor)) * percent / 100;

		if (target->query("character") == "��������")
			wound -= wound * 20 / 100;

		if (wound > 0)
		{
			wound = COMBAT_D->calc_wound(me, target, wound);
			target->receive_wound("qi", wound, me);
		}

		if (functionp(final)) final = evaluate(final);

		if (stringp(final))
		{
			if (sscanf(final, "%s@%s", final, limb) == 2)
			{
				if (sscanf(final, "%s:%s", result, damage_type) != 2)
				{
					result = HIR "���д��˸����У�";
					damage_type = final;
				}
				if (sscanf(limb, "?%*s"))
				{
					// auto select limb
					limbs = target->query("limbs");
					if (! arrayp(limbs))
					{
						limbs = ({ "����" });
						target->set("limbs", limbs);
					}
					limb = limbs[random(sizeof(limbs))];
				}

				// indicate damage type & limb
				final = replace_string(damage_msg(damage, damage_type), "$l", limb);
				final = replace_string(final, "$n", "$n" HIR);
				final = replace_string(final, "$N", "$N" HIR);
				final = replace_string(final, "$p", "$p" HIR);
				final = replace_string(final, "$P", "$P" HIR);
				if (weapon)
					final = replace_string(final, "$w", weapon->name() + HIR);
				final = result + HIR + final + NOR;
			}

			msg += final;
			msg += "( $n" + eff_status_msg(target->query("qi") * 100 / target->query("max_qi")) + ")\n";
		}

		break;
	}

	if (foo_after_hit) msg += foo_after_hit;
	if (foo_before_hit) msg = foo_before_hit + msg;

	// Clear the special message info after damage info
	foo_before_hit = 0;
	foo_after_hit = 0;

	return msg;
}

varargs string do_respond(object me, object target, int damage, int percent, mixed final)
{
	int armor;
	int wound;
	string msg;
	string skill;
	string damage_type;
	string result;
	int str;

	// Check the target's armor
	armor = target->query_temp("apply/armor");

	msg = "";

	while (damage > 0)
	{
		if (target->is_busy()) target->interrupt_me(target, 4 + random(4));

		str = me->query_str() + me->query_temp("str");

		if (str < 20) damage += damage * str / 50;
		else if (str < 40) damage += damage * ((str - 20) / 2 + 20) / 50;
		else damage += damage * ((str - 40) / 4 + 30) / 50;

		if (damage < 1) break;

		if (damage > 1500)	damage = (damage - 1500) / 4 + 1000;
		else if (damage > 500)	damage = (damage - 500) / 2 + 500;

		damage = COMBAT_D->calc_damage(me, target, damage);
		target->receive_damage("qi", damage, me);
		wound = (damage - random(armor)) * percent / 100;

		if (target->query("character") == "��������")
			wound -= wound * 20 / 100;

		if (wound > 0)
		{
			wound = COMBAT_D->calc_wound(me, target, wound);
			target->receive_wound("qi", wound, me);
		}

		if (stringp(final))
		{
			msg += final;
			msg += "( $N" + eff_status_msg(target->query("qi") * 100 / target->query("max_qi")) + ")\n";
		}

		break;
	}

	return msg;
}

//      fight()
//
void fight(object me, object victim)
{
	object ob;
	object weapon;
	string askill;
	int    double_attack;
	mapping prepare;
	string result;
	mapping my_temp;

	if (! living(me)) return;

	if (! mapp(my_temp = me->query_entire_temp_dbase()))
		my_temp = ([ ]);

	prepare = me->query_skill_prepare();
	if (weapon = my_temp["weapon"])
		askill = weapon->query("skill_type");
	else if (! prepare || sizeof(prepare) == 0) askill = "unarmed";
	else if (sizeof(prepare)) askill = (keys(prepare))[0];
	if (askill == "pin") askill = "sword";

	askill = me->query_skill_mapped(askill);
	if (askill && random(me->query_dex()) >= 8)
		double_attack = (sizeof(prepare) >= 2 && ! weapon) ||	SKILL_D(askill)->double_attack();

	// If victim is busy or unconcious, always take the chance to make an attack.
	if (victim->is_busy() || ! living(victim))
	{
		me->set_temp("guarding", 0);
		if (! victim->is_fighting(me)) victim->fight_ob(me);
		do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);

		if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
		{
			me->set_temp("action_flag",1);
			do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);
			me->set_temp("action_flag",0);
		}

	// Else, see if we are brave enough to make an aggressive action.
	} else
	if (me->query_str() > random(victim->query_str() * 3 / 4))
	{
		me->set_temp("guarding", 0);
		if (! victim->is_fighting(me))
			victim->fight_ob(me);
		do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);

		if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
		{
			me->set_temp("action_flag",1);
			do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);
			me->set_temp("action_flag",0);
		}

	// Else, we just start guarding.
	} else
	if (! me->query_temp("guarding"))
	{
		me->set_temp("guarding", 1);
		message_combatd( guard_msg[random(sizeof(guard_msg))], me, victim, "",0,"");
		return;
	} else return;
}

//      auto_fight()
//
//      This function is to start an automatically fight. Currently this is
//      used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
	// Don't let NPC autofight NPC.
	if (! userp(me) && ! userp(obj)) return;

	if (me->query_temp("owner") == obj ||
	    obj->quety_temp("owner") == me)
		return;

	// Because most of the cases that we cannot start a fight cannot be checked
	// before we really call the kill_ob(), so we just make sure we have no 
	// aggressive callout wating here.
	if (me->query_temp("looking_for_trouble")) return;
	me->set_temp("looking_for_trouble", 1);

	// This call_out gives victim a chance to slip trough the fierce guys.
	call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
	int shen;

	// Are we still exist( not becoming a corpse )?
	if (! me || ! obj || ! living(me)) return;

	me->set_temp("looking_for_trouble", 0);

	if (me->is_fighting(obj) ||
	    environment(me) != environment(obj) ||
	    (environment(me)->query("no_fight") && !obj->query_condition("killer")))
		return;

	shen = 0 - (int)me->query("shen");
	message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);

	if (! userp(me) || (int)me->query("neili") > (random(shen) + shen)/10 )
		return;

	if (shen > (int)me->query("score") && ! wizardp(obj))
	{
		message_vision("$N����$n�ȵ���" + RANK_D->query_self_rude(me) + "����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n", me, obj);
		me->kill_ob(obj);
		if (living(obj) && ! userp(obj))
			obj->kill_ob(me);
		else
			obj->fight_ob(me);
	} else
	{
		message_vision("$N����$n�ȵ���ι��" + RANK_D->query_rude(obj) + "��" + RANK_D->query_self_rude(me) + "�������˴�ܣ����������ְɣ�\n", me, obj);
		me->fight_ob(obj);
		obj->fight_ob(me);
	}
}

void start_hatred(object me, object obj)
{
	if (! me || ! obj || ! living(me))
		return;

	me->set_temp("looking_for_trouble", 0);

	if (me->is_fighting(obj) || environment(me) != environment(obj) || 
		(environment(me)->query("no_fight") && !obj->query_condition("killer")))
		return;

	if (me->query_temp("owner") == obj->query("id") ||
	    obj->query_temp("owner") == me->query("id"))
		return;

	// We found our hatred! Charge!
	if (me->query("can_speak"))
		message_vision(catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);

	me->want_kill(obj);
	me->kill_ob(obj);
	if (living(obj) && ! userp(obj))
		obj->kill_ob(me);
	else
		obj->fight_ob(me);

	if (! playerp(me) && me->is_busy() && ! intp(me->query_busy()))
		me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
	if (! me || ! obj || ! living(me))
		return;

	me->set_temp("looking_for_trouble", 0);

	if (me->is_fighting(obj) ||
	    environment(me) != environment(obj) ||
	    (environment(me)->query("no_fight") && !obj->query_condition("killer")))
		return;

	// We found our vendetta opponent! Charge!
	me->want_kill(obj);
	me->kill_ob(obj);
	if (living(obj) && ! userp(obj))
		obj->kill_ob(me);
	else
		obj->fight_ob(me);
}

void start_aggressive(object me, object obj)
{
	if (! me || ! obj || ! living(me)) return;

	me->set_temp("looking_for_trouble", 0);

	if (me->is_fighting(obj) ||
	    environment(me) != environment(obj) ||
	    (environment(me)->query("no_fight") && !obj->query_condition("killer")))
		return;

	// We got a nice victim! Kill him/her/it!!!
	me->want_kill(obj);
	me->kill_ob(obj);
	if (living(obj) && ! userp(obj))
		obj->kill_ob(me);
	else
		obj->fight_ob(me);
}

int player_escape(object killer, object ob)
{
	object iob;
	string msg;

	if (! objectp(ob))
		return 0;

	// �����ô��
	if (! playerp(ob))
		return 0;

	if ((int)ob->query("combat/which_day") == time() / 86400 &&
	    (int)ob->query("total_count") > 0)
		return 0;

	// ����ε��ˣ��쿴�Ƿ��Ǳ�����������ε�
	if (! killer) killer = ob->query_defeated_by();
	if (! killer || ! playerp(killer) ||
	    ! killer->is_want_kill(ob->query("id")))
		return 0;

	if (ob->query("combat_exp") >= 150000)
		return 0;

	switch (random(7))
	{
	case 0:
		msg = "ͻȻֻ������һ����̾��һ�����ᰴ����$N���һ��������"
		      "���˼����ֻ��̧��һ�񡣴�æ֮��ֻ�¶��ֹ�����������"
		      "���мܣ���æ���Ծ����ȴ�����˲���׷����ֻ��һ������"
		      "��$n��ת��ƮȻ��ȥ��������Ȼ��\n";
		break;

	case 1:
		msg = "$N��$n���ڵأ���������һ��Ц����δ���£�ֻ��������"
		      "��һ������Ȼ���Ʒ�Ϯ�壬$N�ٸк���������������Ϣ����"
		      "æ�м�æ�˺󣬴������ȽŸ���ȴ��$n������Ӱ���١�\n";
		break;

	case 2:
		msg = "һ�˺�Ȼ�������ȵ��������д�������������޴�������"
		      "��֮�������ߣ���˵��һ�ƻ�����$N�����мܣ�һ��֮�¼�"
		      "����Ѫ��ֻ��������������$n����Ц������ת����ȥ��$N��"
		      "��֮�£���Ȼ˵����һ�仰����\n";
		break;

	case 3:
		msg = "ͻȻһ�˺ȵ�������������ֻ��һ����Ӱ�ӵ�������һ�Ž�"
		      "$N���˸���ͷ����������$n�������$N����������������δ"
		      "����������������������ȥ�ɣ���$N������������ס��Ϣ"
		      "���������Ŀ�������ȥ�ˡ�\n";
		break;

	case 4:
		msg = "$N��ǰһ������Ȼ������ǰ�Ѷ������ˣ�һ��һ�ݣ�һϲһ"
		      "ŭ�����ɰ�����񼡣һ����������һ��ͭ�ƣ�Ц��������λ" +
		      RANK_D->quert_respect(killer)+ "�����淣��ͭ�������¿�"
		      "�ã���$N���˴��һ������ֻ��һ�����ﻹ�Ҵ��仰��"
		      "���������俴�˹�����Ŀ����磬$NڨڨЦ��������Ŀ����"
		      "�˴���$n��ң��ȥ��\n";

	case 5:
		msg = "ǡ�ڴ�ʱ������һ����·����ֻ����΢һ�ü���ȵ�����أ"
		      "��" + RANK_D->query_rude(killer)+ "��������������$N��"
		      "ŭ���������Ǻ��ˣ�������ţ������ߴ�ŭ��һ�����䣬$N"
		      "����ֻ��һ�񣬡����ࡱһ��˫���������У����а�ߡ���"
		      "��ɭȻ�������������͵�ľ������Ҳ�����в�����������"
		      "������ʱ$N��Ϣ������䳡�滰Ҳ˵��������ֻ���ۿ�$n"
		      "����ľ����������ȥ��\n";
		break;

	default:
		msg = "������������һ��Ц��һ�˵��������֣��벻��������ʮ"
		      "�겻����������Щ���ָ���ȴ��Խ��Խ�������ˣ�����һ��"
		      "���������ǣ��������Ʒ����������ڣ����޾�ͷ����$N��"
		      "�ô��乶��£������ķ�ȴ��һ�ˣ�ת��ͷ�������Ǵ��"
		      "һ������$nҲ�����ˡ�\n";
		break;
	}

	if ((environment(killer) == environment(ob)) &&
	    killer->is_fighting(ob))
	{
		msg = replace_string(msg, "$n", ob->name());
		message_sort(msg, killer);
	} else
	{
		msg = "����һ����·��������" + ob->name() + "�ε��ڵأ�̾��"
		      "����������������ˡ�\n";
		message("vision", msg, environment(ob));
	}


	// �����ϴ��Ķ�������
	foreach (iob in all_inventory(ob))
//		if (! iob->query("money_id") && ! iob->query("owner_id") && ! iob->query("equipped"))
                if ( iob->query("id")=="shaolin wuji")
			iob->move(environment(ob));


	// ��ʼ����ҵ�״̬
	ob->clear_condition();
	ob->remove_killer(killer);
	killer->remove_killer(ob);

	// ͨ����������
	if (! killer->query_condition("killer"))
	{
		msg = "��˵�ٸ����º������飬������������" + killer->name(1) + "��";
		killer->apply_condition("killer", 900);
	} else
	{
		msg = "��˵�ٸ��ӽ�׽���۴����˵ı�ͽ" + killer->name(1) + "��";
		killer->apply_condition("killer", 900 + (int)killer->query_condition("killer"));
	}
	CHANNEL_D->do_channel(this_object(), "rumor", msg);

	ob->move("/d/xiakedao/shiroom24");
	ob->set("startroom", "/d/xiakedao/shiroom24");
	ob->revive();
	ob->set("eff_qi", ob->query("max_qi"));
	ob->set("eff_jing", ob->query("max_jing"));
	ob->set("qi", 0);
	ob->set("jing", 0);

	if (intp(ob->query_busy()))
		ob->start_busy(30);

	tell_object(ob, "������������������λ�������ھ���������\n"
		    HIG "�����������㣺" + RANK_D->query_respect(ob) +
			"����Ҫ���뵺��������˵һ��(ask long about �뵺)��"NOR"\n");

	return 1;
}

void announce(object ob, string event)
{
      
	switch (event)
	{
	case "kuilei":
		message_vision(NOR"$Nʹ��������ܻ���һ���׹���ʧ�ˣ�\n", ob);
		
		break;

	case "dead":
		message_vision(NOR"$N���˼���" HIR "��Ѫ" NOR "���ڵ��ϳ鶯�˼��¾����ˣ�\n", ob);
		
		break;

	case "unconcious":
		message_vision("\n"NOR"\n$N����һ�����ȣ����ڵ��ϻ��˹�ȥ��\n", ob);
		player_escape(0,ob);
		break;

	case "revive":
		message_vision("$N���������۾��������˹�����\n", ob);
		break;
	}
}

// called when winner hit the victim to unconcious
void winner_reward(object winner, object victim)
{
	object owner;
	int temp;
	int td;
	mapping today;

	owner = winner->query_temp("owner");
	if (objectp(owner))
		winner = owner;

	winner->defeated_enemy(victim);

	if (! playerp(winner) || wizardp(victim) && 0)
		return;

	if (! winner->is_want_kill(victim->query("id")))
		// only if I want kill ob, I will record it.
		return;

	winner->add("combat/DPS", 1);
	if (victim->is_not_bad())  winner->add("combat/DPS_NOTBAD", 1);
	if (victim->is_not_good()) winner->add("combat/DPS_NOTGOOD", 1);
	if (victim->is_bad())      winner->add("combat/DPS_BAD", 1);
	if (victim->is_good())     winner->add("combat/DPS_GOOD", 1);

	if (victim->query_condition("killer"))
		return;

	if (victim->query("combat_exp") < 150)
		return;

	log_file("static/killrecord",
		 sprintf("%s %s defeat %s\n",
			 log_time(), log_id(winner), log_id(victim)));

	td = time() / 86400;
	today = winner->query("combat/today");
	if (! mapp(today) || today["which_day"] != td)
	{
		today = ([ "which_day" : td,
			   "total_count" : 1,
			   victim->query("id") : 1, ]);
	} else
	{
		// count how many times that winner hit the victim to unconcious
		temp = ++today[victim->query("id")];
		if (temp == query("pk_perman"))
		{
			// reach limit
			tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
				    victim->name() + chinese_number(temp) +
				    "���ˣ�������"
				    "��ɣ������鷳��Ҫ�������ˡ�"NOR"\n");
		} else
		if (temp > query("pk_perman"))
			// too many times
			winner->set("combat/need_punish", "���˱���̫�����������д���");

		// count how many users that winner hit to unconcious
		temp = ++today["total_count"];
		if (temp == query("pk_perday"))
		{
			// reach limit
			tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
				    chinese_number(temp) + "������ˣ�������"
				    "��ɣ������鷳��Ҫ�������ˡ�"NOR"\n");
		} else
		if (temp > query("pk_perday"))
			// too many users
			winner->set("combat/need_punish", "ɥ��������������¾�����޿�ˡ��");
	}
	winner->set("combat/today", today);
}

void killer_reward(object killer, object victim)
{
	object owner;
	string vmark;
	object box,*inv;
	string msg = "Ī�����������";
	string follow_msg = 0;
	object weapon;
	mapping actions;
	int i,shen_delta;
	mapping ks, vs, kcombat;
	int win_exp;
	if (! objectp(victim))
		return;

	if (objectp(killer))
	{
		owner = killer->query_temp("owner");
		if (objectp(owner))
			killer = owner;
	}

	// This while is only to enable "break"
	vs = victim->query_entire_dbase();
	while (1)
	{
		if (! objectp(killer))
			break;

		// call the killer's override function
		killer->killed_enemy(victim);

		if (! objectp(killer) || ! playerp(killer))
			break;

		// assure the killer's dbase
		ks = killer->query_entire_dbase();
		if (! mapp(kcombat = ks["combat"]))
		{
			kcombat = ([ ]);
			ks["combat"] = kcombat;
		}

		// adjust the "shen" & "experience" of the killer
		if (ks["combat_exp"] < vs["combat_exp"])
		{
			win_exp=1;

			if(random(20)==1)
			{
				tell_object(killer,"\n"HIM"<��ϲ>:"NOR"  ��"HIR"ɱ����"NOR+victim->query("name")+HIG", ����:"GRN"���������䡿"NOR"... "HIY"  <���⾭��>: "NOR+HIG+win_exp+YEL+" ��" NOR"\n");
				box=new("/clone/box/chuji_box"); 
				box->move(environment(killer));
			}

			ks["combat_exp"]+=win_exp;
			
			if (ks["combat_exp"] >= 100000 && ks["combat_exp"] >= vs["combat_exp"] * 2 / 3)
			{
				// adjust experience
				if (! intp(ks["experience"]))
					ks["experience"] = 0;
				killer->improve_experience(1 + random(5));
			}

			// adjust shen
			shen_delta = -vs["shen"] / 10;
			if (shen_delta > 100)
			{
				// ������У����õ�����
				shen_delta = (shen_delta - 100) / 3 + 100;

				if (shen_delta > 200)
					shen_delta = (shen_delta - 200) / 3 + 200;

				if (shen_delta > 300)
					shen_delta = (shen_delta - 300) / 3 + 300;
			} else
			if (shen_delta < -100)
			{
				// ������У����õĸ���
				shen_delta = (shen_delta + 100) / 3 - 100;

				if (shen_delta < -200)
					shen_delta = (shen_delta + 200) / 3 - 200;

				if (shen_delta < -300)
					shen_delta = (shen_delta + 300) / 3 - 300;
			}
					
			ks["shen"] += shen_delta;
		}

		// weapon get the bonus
		if ((weapon = killer->query_temp("weapon")) ||
		    (weapon = killer->query_temp("armor/hands")))
			weapon->killer_reward(killer, victim);

		// record the user's killing
		if (userp(victim))
		{
			if (! intp(kcombat["PKS"]))
				kcombat["PKS"] = 1;
			else
				kcombat["PKS"]++;

			// do family action
			FAMILY_D->family_kill(killer, victim);

			// do league action
			LEAGUE_D->league_kill(killer, victim);

			if (victim->query_condition("killer"))
			{
				follow_msg = "��˵ɱ������" + victim->name(1) + "��" + killer->name(1) + "��" +
					     environment(victim)->short() + HIM"�͵������ˡ�";
				break;
			}

			if (! killer->is_want_kill(vs["id"]))
				break;

			if (! intp(kcombat["WPK"]))
				kcombat["WPK"] = 1;
			else
				kcombat["WPK"]++;

			if (! killer->query_condition("killer"))
			{
				follow_msg = "��˵�ٸ����º������飬����ɱ������" + killer->name(1) + "��";
				killer->apply_condition("killer", 900);
			} else
			{
				follow_msg = "��˵�ٸ��ӽ�׽���۷��ذ��ı�ͽ" + killer->name(1) + "��";
				killer->apply_condition("killer", 900 + (int)killer->query_condition("killer"));
			}

			// assure data of kcombat
			if (! intp(kcombat["WPK_NOTBAD"])) kcombat["WPK_NOTBAD"] = 0;
			if (! intp(kcombat["WPK_NOTGOOD"])) kcombat["WPK_NOTGOOD"] = 0;
			if (! intp(kcombat["WPK_GOOD"])) kcombat["WPK_GOOD"] = 0;
			if (! intp(kcombat["WPK_BAD"])) kcombat["WPK_BAD"] = 0;

			// record the combat info.
			if (victim->is_not_bad())  kcombat["WPK_NOTBAD"]++;
			if (victim->is_not_good()) kcombat["WPK_NOTGOOD"]++;
			if (victim->is_good())     kcombat["WPK_GOOD"]++;
			if (victim->is_bad())      kcombat["WPK_BAD"]++;
			break;
		}

		if (vs["can_speak"])
			if (! intp(kcombat["MKS"]))
				kcombat["MKS"] = 1;
			else
				kcombat["MKS"]++;

		break;
	}

	// die penalty & message of victim
	if (playerp(victim)&&victim->query_temp("kuilei_used"))
	{
		// clear punish info.
		if (objectp(killer) && killer->is_punisher())
			victim->delete("combat/need_punish");

		// clear all condition
		victim->clear_condition();

		// remove vendetta
		map_delete(vs, "vendetta");

		// generate message of die reason
		if (objectp(killer) && killer->is_character())
		{
			msg = "��" + filter_color(killer->name(1));
			actions = killer->query_action();
			switch (mapp(actions) ? actions["damage_type"] : "ɱ��") {
			case "����":
			case "����":
				msg+="������";
				break;
			case "����":
				msg+="������";
				break;
			case "����":
			case "����":
				msg+="������";
				break;
			case "����":
				msg+="������";
				break;
			default:
				msg+="ɱ����";
			}
		}
		if (stringp(victim->query_temp("die_reason")))
			msg = filter_color(victim->query_temp("die_reason"));

		victim->delete_temp("die_reason");
		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("��˵%s" HIM + msg + "��", victim->name(1)));

		// show the follow msg after victim die
		if (follow_msg)
			CHANNEL_D->do_channel(this_object(), "rumor",
					      follow_msg);

		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("��˵%s" HIM + "ʹ�������������ȥ�������ͷ���", victim->name(1)));

		victim->set("combat/last_die", filter_color(msg));
		if (objectp(killer) && playerp(killer) && playerp(victim))
		{
			string cname;
			object couple;

			log_file("static/killrecord",
				 sprintf("%s %s killed %s\n",
					 log_time(),
					 log_id(killer), log_id(victim)));

			killer->remove_killer(victim);
		}
	}
	else if (playerp(victim))
	{
		// clear punish info.
		if (objectp(killer) && killer->is_punisher())
			victim->delete("combat/need_punish");

		// clear all condition
		victim->clear_condition();

		// adjust shen
		vs["shen"] -= vs["shen"] / 10;

		// adjust combat exp.
		vs["combat_exp"] -= vs["combat_exp"] * 2 / 100;

		// adjust weiwang
		vs["weiwang"] -= vs["weiwang"] / 10;

		// adjust score
		vs["score"] -= vs["score"] / 10;

		// remove vendetta
		map_delete(vs, "vendetta");

		// lost half of potential
		if (vs["potential"] > vs["learned_points"] && vs["combat_exp"] > 337500)
			vs["potential"] += (vs["learned_points"] - vs["potential"]) / 1;

		// lost half of experience
		if (vs["experience"] > vs["learned_experience"])
			vs["experience"] += (vs["learned_experience"] - vs["experience"]) / 1;

		victim->skill_death_penalty();
		inv = all_inventory(victim);
		for(i=0;i<sizeof(inv);i++)
		{
			if(inv[i]->is_item_make()&&inv[i]->query("equipped"))
				inv[i]->owner_death_penalty();
		}

		// generate message of die reason
		if (objectp(killer) && killer->is_character())
		{
			msg = "��" + filter_color(killer->name(1));
			actions = killer->query_action();
			switch (mapp(actions) ? actions["damage_type"] : "ɱ��") {
			case "����":
			case "����":
				msg+="������";
				break;
			case "����":
				msg+="������";
				break;
			case "����":
			case "����":
				msg+="������";
				break;
			case "����":
				msg+="������";
				break;
			default:
				msg+="ɱ����";
			}
		}
		if (stringp(victim->query_temp("die_reason")))
			msg = filter_color(victim->query_temp("die_reason"));

		victim->delete_temp("die_reason");
		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("��˵%s" HIM + msg + "��", victim->name(1)));

		// show the follow msg after victim die
		if (follow_msg)
			CHANNEL_D->do_channel(this_object(), "rumor",follow_msg);

		victim->set("combat/last_die", filter_color(msg));
		if (objectp(killer) && playerp(killer) && playerp(victim))
		{
			string cname;
			object couple;

			log_file("static/killrecord",
				 sprintf("%s %s killed %s\n",
					 log_time(),
					 log_id(killer), log_id(victim)));

			killer->remove_killer(victim);

			// check sadly
			cname = victim->query("couple/id");
			if (cname &&
			    victim->query("gender") == "Ů��" &&
			    victim->query("combat_exp") >= 970000 &&
			    objectp(couple = find_player(cname)) &&
			    couple != killer &&
			    couple->query("static/marry") <= 1 &&
			    victim->query("static/marry") <= 1)
			{
				couple->add("static/sadly", 1);
				tell_object(couple, "�������������" +
					    killer->name(1) + "������" +
					    "����е���һ������İ��ˡ�\n");
			}
		}
	}

	if (stringp(vmark = victim->query("vendetta_mark")) && objectp(killer))
		killer->add("vendetta/" + vmark, 1);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
	mapping p, ap;
	string msg;
	string poison_type;

	if (! mapp(p = ob->query_temp("daub/poison")))
		return;

	if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
		return;

	if (! p["remain"])
		return;

	// affect parameter
	ap = allocate_mapping(4);
	if (ob == me)
		ap["level"] = p["level"] * 9 / 10 + 1;
	else
		ap["level"] = p["level"] * 8 / 10 + 1;
		
	ap["id"]       = p["id"];
	ap["name"]     = p["name"];
	ap["duration"] = 1;

	if (p["remain"] > p["level"])
	{
		// decrase the remain poison
		p["remain"] -= p["level"];
	} else
	{
		// the poison has run out
		ob->delete_temp("daub");
	}

	msg = HIG "ͻȻ$n�������˵ĵط���һЩ����";
	if (p["id"] == victim->query("id"))
	{
		if (! victim->query_temp("has_announce/defense1"))
		{
			victim->set_temp("has_announce/defense1", 1);
			victim->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", victim :), victim), 15);
			msg += "��"NOR"\n" HIC "$nĬһ�˹�����Ц�������������" +
			       RANK_D->query_rude(me) + "����Ȼ������ǰ��Ū" +
			       RANK_D->query_self_rude(victim) +
			       "��ҩ�����Ǽ���������������ˣ���"NOR"\n";
		} else
			msg += "������$n��û�����⡣"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	if (p["level"] < victim->query_skill("poison", 1))
	{
		if (! victim->query_temp("has_announce/defense2"))
		{
			victim->set_temp("has_announce/defense2", 1);
			victim->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", victim :), victim), 15);
			msg += "��"NOR"\n" HIC "$n�������Σ���Ȼ��Ц����"
			       "������֮�飬Ҳ�Ź⻪����"NOR"\n";
		} else
			msg += "������$n��Ȼ��û�а����������ϡ�"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	if (p["level"] < victim->query_skill("force") / 2)
	{
		if (! victim->query_temp("has_announce/defense3"))
		{
			victim->set_temp("has_announce/defense3", 1);
			victim->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", victim :), victim), 15);
			msg += "��"NOR"\n" HIC "$n����һ������������Ц�������üһ��Ȼ" +
			       (ob == me ? "�����ϴ㶾" : "ʹ�ô㶾����") +
			       "������Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����"NOR"\n";
		} else
			msg += "������$n�������ƺ����޴󰭡�"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	victim->affect_by(poison_type, ap);

	msg += "��������ж��ˡ�"NOR"\n";
	if (p["level"] < victim->query_skill("force"))
	{
		msg += HIG "$n������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	msg += HIR "$n�ƺ�һ�������ƶٻ�����������ʹ�ࡣ"NOR"\n";
	if (! victim->is_busy())
		victim->start_busy(1 + random(2));
	set_ahinfo(msg);
	return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
	mapping p, ap;
	string msg;
	string poison_type;

	if (! mapp(p = ob->query_temp("daub/poison")))
		return;

	if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
		return;

	if (! p["remain"])
		return;

	if (me->query_temp("armor/hands"))
		return;

	// affect parameter
	ap = allocate_mapping(4);
	ap["level"]    = p["level"] * 7 / 10 + 1;
		
	ap["id"]       = p["id"];
	ap["name"]     = p["name"];
	ap["duration"] = 1;

	if (p["remain"] > p["level"])
	{
		// decrase the remain poison
		p["remain"] -= p["level"];
	} else
	{
		// the poison has run out
		ob->delete_temp("daub");
	}

	msg = HIG "ͻȻ$N���û�����Щ����";
	if (p["id"] == me->query("id"))
	{
		if (! me->query_temp("has_announce/defense1"))
		{
			me->set_temp("has_announce/defense1", 1);
			me->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", me :), me), 15);
			msg += "��"NOR"\n" HIC "$NĬһ�˹�����Ц�������������" +
			       RANK_D->query_rude(victim) + "����Ȼ������ǰ��Ū" +
			       RANK_D->query_self_rude(victim) +
			       "�Ķ�ҩ�������·��ϵĶ�ҩ�������ң���"NOR"\n";
		} else
			msg += "������$N��û�����⡣"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	if (p["level"] < me->query_skill("poison", 1))
	{
		if (! me->query_temp("has_announce/defense2"))
		{
			me->set_temp("has_announce/defense2", 1);
			me->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", me :), me), 15);
			msg += "��"NOR"\n" HIC "$N�������Σ���Ȼ��Ц����������֮�飬Ҳ"
			       "�Ź⻪�����������ϴ㶾�Ҿ������ˣ���"NOR"\n";
		} else
			msg += "������$N��Ȼ��û�а����������ϡ�"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	if (p["level"] < me->query_skill("force") / 2)
	{
		if (! me->query_temp("has_announce/defense3"))
		{
			me->set_temp("has_announce/defense3", 1);
			me->start_call_out(bind((: call_other,
				__FILE__, "clear_announce", me :), me), 15);
			msg += "��"NOR"\n" HIC "$N����һ������������Ц���������Ȼ��������"
			       "�㶾����Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����"NOR"\n";
		} else
			msg += "������$N�������ƺ����޴󰭡�"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	me->affect_by(poison_type, ap);

	msg += "��������Щ���"NOR"\n";
	if (p["level"] < me->query_skill("force"))
	{
		msg += HIG "$N������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����"NOR"\n";
		set_ahinfo(msg);
		return;
	}

	msg += HIR "$N�Ų�һ�����ԣ����ƶٻ�����ɫ�ѿ�֮����"NOR"\n";
	me->start_busy(1 + random(2));
	set_ahinfo(msg);
	return;
}

void clear_announce(object me)
{
	if (! objectp(me))
		return;

	me->delete_temp("has_announce");
}

int PVP_DAMAGE_SCALE = 70;  // ��Ҷ����ʱ�˺�����ǰֵ���½�Ϊ 70%
int PVP_WOUND_SCALE  = 60;  // ��Ҷ����ʱ�˺������ֵ���½�Ϊ 60%

int calc_damage(object attacker, object victim, int damage)
{
	damage += (attacker->query_gain_damage()+attacker->query_gain_break());
	if (objectp(attacker) &&
	    objectp(victim) &&
	    playerp(attacker) && 
	    playerp(victim))
	{
		damage = (damage - victim->query_gain_armor() - victim->query_temp("apply/armor")/4) * PVP_DAMAGE_SCALE / 100;
	}
	else damage -= (victim->query_temp("apply/armor")/4 + victim->query_gain_armor());

	if(damage<1) damage = 1;

	return damage;
}

int calc_wound(object attacker, object victim, int wound)
{
	wound += (attacker->query_gain_damage()+attacker->query_gain_break());
	if (objectp(attacker) &&
	    objectp(victim) &&
	    playerp(attacker) && 
	    playerp(victim))
	{
		wound = (wound - victim->query_gain_armor() - random(victim->query_temp("apply/armor"))) * PVP_WOUND_SCALE / 100;
	}

	else wound -= (random(victim->query_temp("apply/armor")) + victim->query_gain_armor());

	if(wound<1) wound = 1;

	return wound;
}
