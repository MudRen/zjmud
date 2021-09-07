// practice.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

void auto_lian(object me,string skill,int times)
{
	if(!me||!me->query_temp("pending/auto_lian"))
		return;
	if(me->is_busy())
		call_out("auto_lian",1,me,skill,times);

	else if(me->query("neili")<500)
	{
                me->force_me("use huxin dan");
                me->force_me("exert recover");
                me->force_me("exert regenerate");
		me->force_me("dazuo "+me->query("max_qi")/2);
		call_out("auto_lian",10,me,skill,times);
	}
	else if( (int)me->query("qi") < me->query("eff_qi"))
	{
		if (SKILL_D("force/recover")->exert(me, me))
		{
                me->force_me("exert regenerate");
			if( (int)me->query("qi") *100/ me->query("eff_qi")<90)
			{
				tell_object(me,"��Ѫ���㣬�ȴ��ָ��С�����\n");
				call_out("auto_lian",10,me,skill,times);
			}
			else
			{
				call_out("auto_lian",1,me,skill,times);
			}
		}
		else
		{
			tell_object(me,"��Ѫ���㣬�ȴ��ָ��С�����\n");
			call_out("auto_lian",10,me,skill,times);
		}
	}
	else
	{
		tell_object(me,"�й��У�������ϰ������������\n");
		tell_object(me,ZJFORCECMD("lian "+skill+" "+times));
	}
}

int main(object me, string arg)
{
	object where = environment(me);
	string skillname;
	string base_skname;
	int skill, skill_basic, times, i;
	int t = time();

	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (t == me->query_temp("time/practice"))
		return notify_fail("��ող���ϰ���������Ҫ������ϰ������ָ����ϰ�Ĵ�������\n");

	if (me->is_fighting())
		return notify_fail("���Ѿ���ս�����ˣ�ѧһ��ʵս����ɡ�\n");

	if (environment(me)->query("no_learn") || environment(me)->query("no_fight"))
		return notify_fail("���޷�������ط�������ϰ��\n");

	if (! arg) return (__DIR__"enable")->main(me, arg);

	if ((sscanf(arg, "%s %d", base_skname, times) != 2))
	{
		return notify_fail(INPUTTXT("��������ϰ������","lian "+arg+" $txt#")+"\n");
	}
	    
	if (times < 1 || times > 9999)
		return notify_fail("��ϰ�����������1�Σ������ܳ���9999�Ρ�\n");

	if (! stringp(skillname = me->query_skill_mapped(base_skname)))
		return notify_fail("��ֻ����ϰ�� enable ָ�������⼼�ܡ�\n");

	skill_basic = me->query_skill(base_skname, 1);
	skill = me->query_skill(skillname, 1);
	if (skill < 1)
		return notify_fail("�����û��ѧ������ܰɣ������ȥ��̱��ˡ�\n");

	if (skill_basic < 1)
		return notify_fail("����ⷽ��ļ��ܻ���һ�ϲ�ͨ����ô��ȴӻ���ѧ��\n");

	if (skill_basic <= skill)
		return notify_fail("���" + to_chinese(base_skname) + "��򲻹������Լ���������" + to_chinese(skillname) + "��ˮƽ��\n");

	notify_fail("�����ڲ�����ϰ����ܡ�\n");
	if (! SKILL_D(skillname)->valid_learn(me)) return 0;

	if (! XUE_CMD->can_learn(me, skillname))
		return 0;

	notify_fail("��������ϰ" + to_chinese(skillname) + "�����ǲ�û���κν�����\n");
	if (! me->can_improve_skill(skillname))
		return notify_fail("Ҳ����ȱ��ʵս���飬�����ϰ��û��������\n");

	me->set_temp("pending/auto_lian",1);
	me->set_temp("time/practice", t);
	for (i = 0; i < times; i++)
	{
		int tmpi;
		tmpi = (skill_basic / 5 + 1);
		if(where->query("practice_room"))
		{
			if(me->query_condition("db_exp"))
				tmpi *= 2;
			else
				tmpi = tmpi*6/5;
		}
		if (SKILL_D(skillname)->practice_skill(me))
			me->improve_skill(skillname, tmpi,skill_basic > skill? 0: 1);
		else break;
	}
	write(HIC "�����Ű�" + to_chinese(skillname) + "����" + chinese_number(i)+"�ˡ�"NOR"\n");
	if (i == 0 && 0 == times)
		write("Ȼ�������̫���ˣ��޷��ٽ����κ���ϰ�ˡ�\n");
	else if (i >= 0 && i < times)
	{
		call_out("auto_lian",1,me,base_skname,times-i);
	}

	return 1;
}

int help(object me)
{
	write(@TEXT
ָ���ʽ��practice|lian <��������> <����>

���ָ��������ϰĳ������ļ��ܣ�������ܱ����Ǿ��� enable ��רҵ���ܡ�

�������ⷽ��Ļ������ܹ��ߣ����Ծ�����ϰֱ����������������������ֻ��
��������ܵĵȼ��йأ����仰˵���ڼ���ϰ��ʹ�����ѧ���������ʤ������
��Ψһ;������Ȼ������֮ǰ������ʵ�������л���㹻�ľ�����������Ļ�
�����ܡ�
TEXT );
	return 1;
}

