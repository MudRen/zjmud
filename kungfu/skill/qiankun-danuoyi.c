// qiankun-danuoyi.c Ǭ����Ų��
// by King 97.05

inherit SKILL;

#include <ansi.h>

string *parry_msg = ({
	"$Nһ�л���$n���ϣ�ȴ��$n����Ǭ����Ų�ƣ�����������������¡�\n",
	"$n����һ����$N�����Լ������ػ��������ŵ������˼�����\n",
	"$n�ֱۻ�ת����$N����������һ�ƣ�$N������ա�\n",
	"$n�����������$N����������һ����$N���Ʋ�ס��ֱ��ǰ��ȥ��\n",
	"$n���β�����$Nһ�л��£�����ʯ���󺣣�������ס�ˡ�\n",
	"$n��ǣ������$N��������������ת�˺ü���Ȧ�ӡ�\n",
	"$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n",
	"$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});

string *dodge_msg = ({
	"$Nһ�л���$n���ϣ�ȴ��$n����Ǭ����Ų�ƣ�����������������¡�\n",
	"$n����һ����$N�����Լ������ػ��������ŵ������˼�����\n",
	"$n�ֱۻ�ת����$N����������һ�ƣ�$N������ա�\n",
	"$n�����������$N����������һ����$N���Ʋ�ס��ֱ��ǰ��ȥ��\n",
	"$n���β�����$Nһ�л��£�����ʯ���󺣣�������ס�ˡ�\n",
	"$n��ǣ������$N��������������ת�˺ü���Ȧ��\n",
	"$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n",
	"$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});

string *pfail_msg = ({
	"$n����Ǭ����Ų�ƣ���ͼ����������������£�Ȼ��$N���ѿ������а�������仯Ī�⡣\n",
	"$n����һ����$N�����Լ������ػ���������æ���У���ת���⣬����$n����ʤ����\n",
	"$n�ֱۻ�ת����$N����������һ�ƣ�Ȼ��$N��������һ�䣬��δ��ա�\n",
	"$n�����������$N����������һ����$N���Ʋ�ס��˳�Ʊ�����ǰֱ����\n",
	"$n��ǣ������$N����������˳�Ʊ��У�Բת���⣬����������\n",
	"$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ȼ���ѣ�������һ�㣬�����Է���\n",
});

int valid_enable(string usage) 
{ 
	return usage == "parry" ;
}

string query_parry_msg(string limb)
{
	return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
	int layer;

	if (me->query("gender") == "����" &&
	    me->query_skill("qiankun-danuoyi", 1) >= 50)
		return notify_fail("����ͼ�����ķ�������Ų�ƣ�ȴ"
				   "��������һ����ã�����Լ�����\n");

	if (me->query_condition("qiankun-except"))
		return notify_fail("������������������֫�Ժ������"
				   "����޷����������񹦡�\n");

	layer = (int)me->query_skill("qiankun-danuoyi", 1) / 50;
	if (layer > 13) layer = 13;

	if (me->query("int") < 22 + layer)
		return notify_fail("����õ�" + chinese_number(layer) +
				   "��Ǭ����Ų��ʵ��������ޱȣ�ȫȻ�޷���⡣\n");

	if ((int)me->query("max_neili") < 2000)
		return notify_fail("�������̫��޷�����Ǭ����Ų�ơ�\n");
	
	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���򲻹����޷���ǿ����Ǭ����Ų�ơ�\n");

	if ((int)me->query_skill("parry", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
		return notify_fail("��Ļ����мܻ�����ޣ��޷����������Ǭ����Ų�ơ�\n");

	if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
		return notify_fail("��Ļ����Ṧ������ޣ��޷����������Ǭ����Ų�ơ�\n");

	if ((int)me->query_skill("force", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
		return notify_fail("��Ļ����ڹ�������ޣ��޷����������Ǭ����Ų�ơ�\n");

	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mapping result;
	string msg;
	int ap, dp, mp;

	if ((int) me->query_skill("qiankun-danuoyi", 1) < 100 ||
	    ! living(me))
		return;

	mp = ob->query_skill("count", 1) + ob->query_skill("never-defeated", 1)/3;
	ap = ob->query_skill("force", 1) + mp;
	dp = me->query_skill("qiankun-danuoyi", 1);

	if ( me->query("int") > ob->query("int"))
	{
          if (ap / 2 + random(ap) < dp) {
		msg = parry_msg[random(sizeof(parry_msg))];
		msg = replace_string(msg, "$N", "$N" HIG);
		msg = replace_string(msg, "$n", "$n" HIG);
		msg = HIG + msg + NOR;
		result = ([ "damage": -damage,
			    "msg"   : msg ]);
		return result;
            } else if (mp >= 100)
	     {
		msg = pfail_msg[random(sizeof(pfail_msg))];
		msg = replace_string(msg, "$N", "$N" HIY);
		msg = replace_string(msg, "$n", "$n" HIY);
		msg = HIY + msg + NOR;
		COMBAT_D->set_bhinfo(msg);
	      }
	} else {
	if ( random(ap) < dp/3 && ap/2<dp)
	{
		msg = parry_msg[random(sizeof(parry_msg))];
		msg = replace_string(msg, "$N", "$N" HIG);
		msg = replace_string(msg, "$n", "$n" HIG);
		msg = HIG + msg + NOR;
		result = ([ "damage": -damage,
			    "msg"   : msg ]);
		return result;
	} else
	if (mp >= 100)
	   {
		msg = pfail_msg[random(sizeof(pfail_msg))];
		msg = replace_string(msg, "$N", "$N" HIY);
		msg = replace_string(msg, "$n", "$n" HIY);
		msg = HIY + msg + NOR;
		COMBAT_D->set_bhinfo(msg);
	    }
      }
}

int practice_skill(object me)
{
	return notify_fail("Ǭ����Ų��ֻ��ͨ��ѧϰ���ж�Ǭ����Ų���ķ���ߡ�\n");
}

string perform_action_file(string func)
{
	return __DIR__"qiankun-danuoyi/" + func;
}

void skill_improved(object me)
{
	int lvl;
	int layer;

	lvl = me->query_skill("qiankun-danuoyi", 1);
	layer = lvl / 50;
	if (layer > 13) layer = 13;

	if (! layer)
	{
		tell_object(me, HIM "��Ǳ������Ǭ����Ų"
			    "���ķ�����������"NOR"\n");
	} else
	if ((lvl % 50) == 0)
	{
		tell_object(me, HIM "���������˵�" + chinese_number(layer) +
			    "���Ǭ����Ų���ķ���"NOR"\n");
	} else
		tell_object(me, HIM "��Ե�" + chinese_number(layer) +
			    "���Ǭ����Ų���ķ��ּ�����һ���˽⡣"NOR"\n");

	if (lvl > me->query_skill("force") * 2 / 3)
	{
		if (lvl < me->query_skill("force") * 2 / 3 + 10)
		{
			tell_object(me, HIG "�������Ϣһ�����ң�����ʱ��ʱ�ȣ����ɵô��һ����\n"
			      "����Ī�����߻���ħ����Ȼ����õ���Խ��Խ�Ǻ��䣬��Ϊ���ܡ�"NOR"\n");
			message("vision", HIG + me->name() + HIG "����ɫ�����"
				"�̣���ò�ͣ��ֻ�ǻ���������ƺ�ʮ��ʹ�ࡣ"NOR"\n",
				environment(me), ({ me }));
			return;
		}

		tell_object(me, HIB "���Ȼ���õ�������һ���⣬��ʱ����֫"
		      "����һ���ú����ޱȣ��̲�ס����������"NOR"\n");
		message("vision", HIB + me->name() + HIB "��Ȼһ"
			"������ɫ��Ȼ��òҰף���Ȼ������һ��������������ֹ��"NOR"\n",
			environment(me), ({ me }));
	} else
	if (lvl < 350 && (lvl * 20 + 400) > me->query("max_neili"))
	{
		if ((lvl * 20 + 400) < me->query("max_neili") + 200)
		{
			tell_object(me, HIR "��������ת��һ����Ϣ��һʱ������"
			      "�����ã��������ǲ�ҪóȻ������Ų���񹦡�"NOR"\n");
			return;
		}

		tell_object(me, HIR "��������ת��һ����Ϣ����Ȼ����һ����"
		      "��Ȼת����������ʱ���н�ʹ���������˼�����Ѫ��"NOR"\n");
		message("vision", HIR + me->name() + HIR "��ɫ��Ȼ"
			"һ�䣬Ż��������Ѫ����Ŀ���ġ�"NOR"\n",
			environment(me), ({ me }));
	} else
		return;

	me->apply_condition("qiankun-except", lvl + (int)me->query_condition("qiankun-except"));
}

int diffcult_level() { return 300; }

