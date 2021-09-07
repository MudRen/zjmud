// learn.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int can_learn(object me, string skill);

string *reject_msg = ({
	"˵������̫�����ˣ�����ô�ҵ���\n",
	"�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
	"Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n",
});

void create() { seteuid(getuid()); }

void auto_learn(object me, string teacher,string skill,int times)
{
	if(!me||!me->query_temp("pending/auto_learn")||!present(teacher,environment(me)))
		return;

	if(me->is_busy())
		call_out("auto_learn",1,me,teacher,skill,times);

	else if(me->query("neili")<302 && me->query("max_neili")>400)
	{
                me->force_me("use huxin dan");
                me->force_me("exert regenerate");
		me->force_me("dazuo "+me->query("max_qi")/2);
		call_out("auto_learn",10,me,teacher,skill,times);
	}

	else if( (int)me->query("jing") < me->query("eff_jing"))
	{
		if (SKILL_D("force/regenerate")->exert(me, me))
		{
			if( (int)me->query("jing") < me->query("eff_jing"))
			{
				tell_object(me,"�����㣬�ȴ��ָ��С�����\n");
				call_out("auto_learn",10,me,teacher,skill,times);
			}
			else
			{
				call_out("auto_learn",1,me,teacher,skill,times);
			}
		}
		else
		{
			tell_object(me,"�����㣬�ȴ��ָ��С�����\n");
			call_out("auto_learn",10,me,teacher,skill,times);
		}
	}
	else
	{
		tell_object(me,"�й��У�������̡�����������\n");
		tell_object(me,ZJFORCECMD("learn "+teacher+" "+skill+" "+times));
	}
}

int main(object me, string arg)
{
	object where = environment(me);
	string *args;
	string skill, teacher, master, skill_name;
	object ob;
	mixed flag;
	int master_skill, my_skill, jing_cost, times, i,up_skill_point;
	int rand;
	int up_point = 0;
	int t = time();

	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

	if (t == me->query_temp("time/learn"))
		return notify_fail("��ող�ѧϰ���������Ҫ����ѧϰ������ָ��ѧϰ�Ĵ�������\n");

	if (! arg || (i = sizeof(args = explode(arg, " "))) < 2)
		return notify_fail("ָ���ʽ��learn|xue <ĳ��> <����> <����>\n");

	i--;
	if (i >= 2 && sscanf(args[i], "%d", times) && times)
		i--;
	else
		return notify_fail(INPUTTXT("������ѧϰ������","learn "+arg+" $txt#")+"\n");
	skill = args[i--];
	if (args[i] == "about" && i >= 1)
		i--;
	teacher = implode(args[0..i], " ");

	if (times < 1 || times > 9999)
		return notify_fail("ѧϰ��������һ�Σ����Ҳ���ܳ���һ��Ρ�\n");

	if (me->is_fighting())
		return notify_fail("����ĥǹ������������\n");

	if (! (ob = present(teacher, environment(me))) || ! ob->is_character())
		return notify_fail("��Ҫ��˭��̣�\n");

	if (! living(ob))
		return notify_fail("��....����Ȱ�" + ob->name() +"Ū����˵��\n");

	if (! me->is_apprentice_of(ob) &&
	    (me->query("family/family_name") != ob->query("family/family_name") ||
	     me->query("family/generation") > ob->query("family/generation") ||
	     me->query("family/generation") < 1 ||
	     ! ob->can_learn_from() ||
	     playerp(ob)))
	{
		switch (ob->recognize_apprentice(me, skill))
		{
		case 0:
			return notify_fail( ob ->name() +
			       reject_msg[random(sizeof(reject_msg))] );
		case -1:
			return 1;
		}
	}

	if (! master_skill = ob->query_skill(skill, 1))
		return notify_fail("���������±����ұ���ѧ�ˡ�\n");

	if (stringp(flag = ob->query("no_teach/" + skill)))
	{
		message_vision(CYN "$N" CYN "ҡҡͷ��˵����" + flag + ""NOR"\n", ob);
		return 1;
	} else
	if (intp(flag) && flag)
	{
		if (flag != -1)
			// show the messaeg if the result was not -1
			write(CYN + ob->name() + CYN "˵�����Բ���" + to_chinese(skill) + "�ɲ�����㴫�ڡ�"NOR"\n");
		return 1;
	}

	if (me->is_apprentice_of(ob) &&
	    SKILL_D(skill)->type() == "martial" &&
	    me->query_skill(skill, 1) >= SKILL_D(skill)->valid_learn_level())
	{
		write(ob->name() + "˵����.... ���" + to_chinese(skill) +
		      "�����Ѿ��Ƿ�ͬ�����ˣ��ҾͲ��ٽ��㣬���Լ����о��ɡ�\n");
		return 1;
	}

	my_skill = me->query_skill(skill, 1);
	if (my_skill >= master_skill)
		return notify_fail("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");

	if (my_skill >= (int)(master_skill - me->query("betrayer/times") * 2))
		return notify_fail(ob->name() + "������üͷ�������������ȥ����ʦ������\n");

	if (! can_learn(me, skill))
		return 0;

	notify_fail("����Ŀǰ��������û�а취ѧϰ���ּ��ܡ�\n");
	if (! SKILL_D(skill)->valid_learn(me)) return 0;

	jing_cost = (100 + my_skill * 2) / (int) me->query("int");
	if (! my_skill)
	{
		jing_cost *= 2;
		me->set_skill(skill,0);
	}

	if ((me->query("potential") - me->query("learned_points")) < times)
		return notify_fail("���Ǳ�ܲ���ѧϰ��ô����ˡ�\n");
	write(sprintf(HIC "�㿪ʼ��%s���" + chinese_number(times) + "���йء�%s�������ʡ�"NOR"\n",ob->name(),to_chinese(skill)));

	if (ob->query("env/no_teach"))
	{
		write("����" + ob->name() + "���ڲ���׼���ش�������⡣\n");
		return 1;

	}

	tell_object(ob, sprintf("%s��������йء�%s�������⡣\n",me->name(), to_chinese(skill)));

	if (! me->can_improve_skill(skill))
	{
		write("Ҳ����ȱ��ʵս���飬���" + ob->name() + "�Ļش������޷���ᡣ\n");
		return 1;
	}

	if (playerp(ob))
	{
		if ((int)ob->query("jing") > jing_cost * times / 5 + 1)
			ob->receive_damage("jing", jing_cost / 5 + 1);
		else
		{
			write("����" + ob->name() + "��Ȼ̫���ˣ�û�а취����ʲ�ᡣ\n");
			tell_object(ob, "������̫���ˣ�û�а취��" + me->name() + "��\n");
			return 1;
		}
	}

	me->set_temp("pending/auto_learn",1);
	me->set_temp("time/learn", t);
	for (i = 0; i < times && i<800 ; i++)
	{
    		if ((int)me->query("jing") < jing_cost)
		{
			if (SKILL_D("force/regenerate")->exert(me, me))
			{
				write("����þ������һЩ����������ѧϰ��\n");
				i--;
				continue;
			}
			else
			{
				me->set("jing", 0);
				break;
			}
		}
		up_skill_point=me->query_int() + my_skill / 4;
		up_skill_point /= 2;
		up_skill_point=5 + random(up_skill_point);
		up_point += up_skill_point;
		me->improve_skill(skill, up_skill_point);
    		me->receive_damage("jing", jing_cost);
		me->add("learned_points", 1);
	}

	if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
 		printf("������%s��ָ�����ԡ�%s�������µ�����"+HIG"exp + "+up_point+" ��"+NOR+"\n", ob->name(),skill_name); 
	else
		printf("������%s��ָ�����ƺ���Щ�ĵá�\n��%s��: "+HIG"exp + "+up_point+" ��"+NOR+"\n", ob->name(),to_chinese(skill));

	if (i == 0 && times==0)
		write("Ȼ�������̫���ˣ��޷��ٽ����κ�ѧϰ�ˡ�\n");
	else if (i >= 0 && i < times)
	{
		call_out("auto_learn",1,me,teacher,skill,times-i);
	}
	return 1;
}

int can_learn(object me, string skill)
{
	string skill_name;
	mapping skills;
	string mskill;
	int tmp;
	int i;

	if (stringp(mskill = SKILL_D(skill)->main_skill()) && mskill != skill && me->query_skill(mskill, 1) > 0)
		return notify_fail("������û�б�Ҫ�ٵ���ѧϰ" + to_chinese(skill) + "�ˡ�\n");

	skills = me->query_skills();
	if (! mapp(skills))
		return 1;

	if (! SKILL_D(skill)->valid_enable("force") ||
	    SKILL_D(skill)->valid_force("*"))
		return 1;

	foreach (skill_name in keys(skills))
	{
		if (file_size(SKILL_D(skill_name) + ".c") == -1)
		{
			continue;
		}

		if (! SKILL_D(skill_name)->valid_enable("force") ||
		    skill_name == skill)
			continue;

		if (! SKILL_D(skill_name)->valid_force(skill))
			return notify_fail("�㲻ɢ��" + to_chinese(skill_name) + "����ôѧϰ" + to_chinese(skill) + "��\n");
	}

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : learn|xue <ĳ��> [about] <����> <����>
 
���ָ������������������й�ĳһ�ּ��ܵ��������⣬��Ȼ������̵Ķ�������
����ϵ�����������ߣ����㾭�����ַ�ʽѧϰ�����ļ���Ҳ�����ܸ��������
�̵��ˣ�Ȼ����Ϊ����ѧϰ��ʽ�൱�һ�֡�����Ĵ��С������ѧϰ����˵����Ϥ
һ���¼������ķ�����

����ѧϰҲ��Ҫ����һЩ�����������ĵľ��������Լ�������ѧϰ����������йء�

�������ָ�� : apprentice, practice, skills, study
HELP
	);
	return 1;
}
