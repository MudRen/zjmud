// abandon.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int skill_lvl, lvl;
    	int jingcost;
	string skill;
    	string name,ok;
	int lost,queren;
	mapping skills;

	if (! arg || arg == "")
		return notify_fail("��Ҫ�������黹��ĳһ��ܣ�\n");

	if(sscanf(arg,"%s %d %d",skill,lvl,queren)==3)
	{
		if(lvl<1)
			return notify_fail("������λ������Ҫ1 ������\n");
	}
	else if(sscanf(arg,"%s %d",skill,lvl)==2)
	{
		if(skill=="exp")
		{
			write(ZJOBLONG"��ȷ��Ҫ����"+lvl+HIY"����"NOR"��\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:abandon "+arg+" 1\n");
			return 1;
		}
		else
		{
			write(ZJOBLONG"��ȷ��Ҫ����"+lvl+"��"HIY+to_chinese(skill)+NOR"��\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:abandon "+arg+" 1\n");
			return 1;
		}
	}
	else skill=arg;

    	if (me->is_fighting())
		return notify_fail("����æ�Ŵ���أ�����ʱ���������£�\n");

    	if (me->is_busy())
		return notify_fail("����æ��û������������\n");

    	jingcost = me->query("int") + random(me->query("int"));
    	if (jingcost > me->query("jing"))
		return notify_fail("���޷����о�����\n");

	if (skill == "exp")
	{
		if (me->query("combat_exp")>1000000 && me->query("zjvip/times")<1)
			return notify_fail("��Ŀǰ�ľ�����ߣ��޷�����ʵս���顣\n");

		if (!queren)
			return notify_fail(INPUTTXT("�����������"ZJBR"����������ٵ�"HIY"����"NOR"��","abandon exp"+" $txt#")+"\n");
		lost = me->query("combat_exp");
		if (lost < lvl)
			return notify_fail("�㷢���Լ����ڶ���ѧ��ֱ����һ����֪��\n");

		if (199999 < lvl)
			return notify_fail("һ�����ֻ������199999ʵս���顣\n");

		message("vision", me->name() + "����������˼��ʲô��\n",environment(me), me);
		tell_object(me, "�㲻����ȭ�ű����Ṧ�ڹ���ֻ��һ����˼�����书��\n");
		me->start_busy(1);

		me->add("combat_exp", -lvl);
		switch (random(6))
		{
		case 0:
			tell_object(me, HIR "���������˺ܶ���ܰ�����£����ɵó������С�"NOR"\n");
			break;
		case 1:
			tell_object(me, HIR "���ƺ��ֿ�����ңԶ��ͯ�꣬һʱ��ȴ�˳�����ķ��ա�"NOR"\n");
			break;
		case 2:
			tell_object(me, HIR "����Ȼһ����̾��ֻ�����Լ�Ϊ����ѧ�ķ�һ����ʵ����ν��"NOR"\n");
			break;
		case 3:
			tell_object(me, HIR "������ֹˮ�����е��书���·����Լ�Զȥ�ˡ�"NOR"\n");
			break;
		case 4:
			tell_object(me, HIR "��̧ͷ������գ�����������͸����˵�����Ľ��ģ��������ľ㻯��"NOR"\n");
			break;
		default:
			tell_object(me, HIR "���Ժ��лι����������̿����������ӣ����ɵð��Կ�Ц��"NOR"\n");
			break;
		}

		UPDATE_D->check_user(me);
		return 1;
	}

    	if (file_size(SKILL_D(skill)+".c")<0)
		return notify_fail("û������ܣ�\n");

    	if (SKILL_D(skill)->type()=="knowledge")
		return notify_fail("֪ʶ�༼�ܲ���������\n");

    	name = to_chinese(skill);
    	if (name[0] < 160) name = "�����";
	if (!queren)
		return notify_fail(INPUTTXT("����������ټ���"HIY+to_chinese(skill)+NOR"��","abandon "+skill+" $txt#")+"\n");

	if (!mapp(skills = me->query_skills())||undefinedp(skills[skill]))
		return notify_fail("�㻹��������ܣ�\n");

	skill_lvl = skills[skill];
	if (! skill_lvl)
	{
		me->delete_skill(skill);
		write("���ˡ�\n");
		return 1;
	}

    	me->start_busy(3 + random(me->query("int") / 7));

    	skill_lvl = skill_lvl - lvl;
    	if (skill_lvl < 1)
    	{
		me->delete_skill(skill);
		write("�㼯�о��������롾" + name + "����������ڽ������������ˡ�\n");
    	} else
    	{
		me->set_skill(skill, skill_lvl);
		write("�㼯�о��������롾" + name + "�����������Ч����\n");
    	}
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��abandon|fangqi <��������> | exp

�������ʵս�������ĳһ������ѧ���ļ��ܣ��ɹ��ʺ�����츳��
�أ�ֻ���ܹ���Ϣ�ĵط����ܹ��������������书�����������
�ܵ���Ϊ�Ƚϸߣ�һ�β�һ���ܹ����׵����ǡ�

��ʱ����Ϊ�书��˻����㲻�ٴ�����ĳ��������¹��򣬾Ϳ���
ʹ������ָ���������
TEXT );
	return 1;
}
