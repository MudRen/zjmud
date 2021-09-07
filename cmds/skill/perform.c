// perform.c

#include <ansi.h>

inherit F_CLEAN_UP;

private int do_perform(object me, string arg);

int main(object me, string arg)
{
	mapping smap, pmap, pfms,skips;
	string force_ski,parry_ski,weapon_ski,and,*pfm,ski_type,uski_type;
	int result;
	int busy;
	int lvl,i,j,k,flag;
	string msg,*valid_types,*skis;
	object env,weapon;

	seteuid(getuid());

	if (me->is_busy())
		return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");

	env = environment(me);
	if(env&&env->is_comb_ob()&&env->query("first")!=me)
		return notify_fail("�𼱣����ֵ�����˵��\n");

	smap = me->query_skill_map();

	pmap = me->query_skill_prepare();

	if(objectp(weapon = me->query_temp("weapon")))
		ski_type = weapon->query("skill_type");

	if (!arg)
	{
		valid_types = ({"finger","hand","cuff","claw","strike","unarmed"});
		skips = ([]);
		j = 3;
		msg = ZJBTSET"b1:����"ZJBR"��Ѫ:exert recover"ZJSEP"b2:����"ZJBR"�ؾ�:exert regenerate"ZJSEP"b3:ŭ��"ZJBR"����:burning"ZJSEP;
		if(!mapp(smap)||smap==([]))
		{
			while(j<11)
			{
				j++; if(j>11) continue;
				msg += "b"+ j + ":��δ"ZJBR"�趨:look"+ZJSEP;
			}
			write(msg+"\n");
			return 1;
		}

		if(force_ski=smap["force"])
		{
			pfms = SKILL_D(force_ski)->query_pfm();
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					j++; if(j>11) continue;
					msg += "b"+ j + ":" + pfms[pfm[i]]+" "+pfm[i]+ZJSEP;
				}
			}
			skips[force_ski]=1;
		}

		if(objectp(weapon))
		{
			if(stringp(weapon_ski=smap[ski_type])&&!skips[weapon_ski])
			{
				pfms = SKILL_D(weapon_ski)->query_pfm();
				if(mapp(pfms)&&pfms!=([]))
				{
					pfm = sort_array(keys(pfms), (: strcmp :) );
					for(i=0;i<sizeof(pfm);i++)
					{
						j++; if(j>11) continue;
						msg += "b"+ j + ":" + pfms[pfm[i]]+" "+ski_type+"."+pfm[i]+ZJSEP;
					}
				}
				skips[weapon_ski]=1;
			}
		}
		else if(!objectp(weapon))
		{
			if(mapp(pmap)&&pmap!=([]))
			{//��������׼������
				skis = sort_array(keys(pmap), (: strcmp :) );
				for(k=0;k<sizeof(skis);k++)
				{
					if(skips[pmap[skis[k]]]) continue;
					pfms = SKILL_D(pmap[skis[k]])->query_pfm();
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							j++; if(j>11) continue;
							msg += "b"+ j + ":" + pfms[pfm[i]]+" "+skis[k]+"."+pfm[i]+ZJSEP;
						}
					}
					skips[pmap[skis[k]]]=1;
				}
			}

			skis = sort_array(keys(smap), (: strcmp :) );
			for(k=0;k<sizeof(skis);k++)
			{
				flag = 1;
				for(i=0;i<sizeof(valid_types);i++)
				{
					if(SKILL_D(smap[skis[k]])->valid_enable(valid_types[i]))
					{
						uski_type = valid_types[i];
						flag = 2;
					}
				}
				if(!skips[smap[skis[k]]]&&flag==2)
				{
					pfms = SKILL_D(smap[skis[k]])->query_pfm();
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							j++; if(j>11) continue;
							msg += "b"+ j + ":" + pfms[pfm[i]]+" "+skis[k]+"."+pfm[i]+ZJSEP;
						}
					}
				}
				skips[smap[skis[k]]]=1;
			}
		}
		while(j<11)
		{
			j++;
			msg += "b"+ j + ":��δ"ZJBR"�趨:look"+ZJSEP;
		}
		write(msg+"\n");
		return 1;
	}

	if (! mapp(smap) || sizeof(smap) == 0)
		return notify_fail("������û��ʹ���κ���Ч���⼼�ܣ�û���⹦�������á�\n");

	if (sscanf(arg, "%s and %s", arg, and) == 2 || sscanf(arg, "%s twice", arg) == 1 && (and = arg))
	{
		lvl = me->query_skill("zuoyou-hubo", 1);
		if (! lvl)
			return notify_fail("��Ҫ��ʲô����Ϊ�Լ�����ͷ���۰���\n");

		if (me->query_skill("count", 1))
			return notify_fail("����ѧ̫�࣬��ͷ���ң����Է��Ķ��á�\n");

		if (lvl <= 100)
			return notify_fail("������һ�����Ϊ̫ǳ�����Է��Ķ��á�\n");

		if (! me->is_fighting())
			return notify_fail("ֻ��ս���в���ʩչ���һ�����\n");

		if (lvl < 360 && random(lvl) < 100)
		{
			me->start_busy(1);
			write("����ͼ���Ķ��ã������־��ǲ���ʹ����\n");
			return 1;
		}
	}

	result = do_perform(me, arg);
	if (! and)
		return result;

	if(result && (arg==and))
		me->set_temp("clear_pfm_mark",1);
	if (! result)
		write(query_notify_fail());
	else
	{
		switch (random(4))
		{
		case 0:
			msg = HIY "$N" HIY "���һ����˫�ַ�ʹ���У�һ�𹥳���"NOR"\n";
			break;

		case 1:
			msg = HIY "$N" HIY "˫���������ʹ��ͬ��ʽ�������ۻ����ҡ�"NOR"\n";
			break;

		case 2:
			msg = HIY "$N" HIY "�����ַ�ʹ���У�����ͣ�ͣ���������ͬʱ������"NOR"\n";
			break;

		case 3:
			msg = HIY "$N" HIY "����һ�У�����һ�У�������·���죬�������Եֵ���"NOR"\n";
			break;
		}

		message_combatd(msg, me);
	}

	busy = me->query_busy();
	me->interrupt_busy(0);

	result = do_perform(me, and);
	if (! result)
		write(query_notify_fail());

	if (intp(busy) && intp(me->query_busy()) && busy > me->query_busy())
	{
		me->interrupt_busy(0);
		me->start_busy();
	}

	return 1;
}

private int do_perform(object me, string arg)
{
	object env,weapon;
	string martial, skill;
	int result;

	if (sscanf(arg, "%s.%s", martial, arg) != 2)
	{
		if (weapon = me->query_temp("weapon"))
			martial = weapon->query("skill_type");
		else
			martial = "unarmed";
	}

	me->clean_up_enemy();
	if (stringp(skill = me->query_skill_mapped(martial)))
	{
		if(me->query_temp("clear_pfm_mark"))
		{
			SKILL_D(skill)->clear_pfm_cd(me, arg);
			SKILL_D(martial)->clear_pfm_cd(me, arg);
			me->delete_temp("clear_pfm_mark");
		}
		notify_fail("����CD�л�����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
		env = environment(me);
		if (SKILL_D(skill)->perform_action(me, arg))
		{
			if (random(120) < (int)me->query_skill(skill))
				me->improve_skill(skill, 1, 1);
			if(env&&env->is_comb_ob()&&env->query("first")==me)
			{
				me->set_temp("pfm_cmd",1);
				env->delete("first");
			}
			return 1;
		} else
		if (SKILL_D(martial)->perform_action(me, arg))
		{
			if (random(120) < (int)me->query_skill(martial, 1))
				me->improve_skill(martial, 1, 1);
			if(env&&env->is_comb_ob()&&env->query("first")==me)
			{
				me->set_temp("pfm_cmd",1);
				env->delete("first");
			}
			return 1;
		}
		return 0;
	}

	return notify_fail("�����ڵ�" + to_chinese(martial)[4..7] + "(" + martial + ")�в�û�������⹦��\n");
}

int help (object me)
{
	write(@HELP
ָ���ʽ��perform | yong [<�书����>.]<��ʽ����> [<ʩ�ö���>]
	  perform | yong ��ʽ1 [<����1>] and ��ʽ2 [<����2>]
	  perform | yong ��ʽ1 [<����1>] twice

�������ѧ���⹦(ȭ�š�����������....)��һЩ����Ĺ�����ʽ��
��ʽ�����������ָ����ʹ�ã���������� enable ָ��ָ����ʹ��
���书����ָ���书����ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ����
��ʱ���Ǳ��е��书��

��������⹦�������಻ͬ��������ʽ������ͬ�ģ����߲����ȭ��
���������ܵ��书(���Ṧ)�������� <�书>.<��ʽ>  �ķ�ʽָ����
�磺

perform sword.chan

���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������ָ
��ʹ�á�

����㾫ͨ���һ���������ͬʱʹ��������ʽ����ͬһ���ֻ���ֱ�
�������ˡ����һ���������Խ�Ǿ����ɹ���Խ�ߡ�

ʹ�� twice ������ʾ������ʹ��ͬ������ʽ��
HELP );
	return 1;
}
