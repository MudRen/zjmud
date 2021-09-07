//cmds/std/
//�������

#include <ansi.h>
 
inherit F_CLEAN_UP;
int check_ip(object *team)
{
	int i, j;
	for (i = 0;i < sizeof(team);i ++) {
		for (j = i + 1;j < sizeof(team);j ++) {
			if (team[i] && team[j] && query_ip_number(team[i]) == query_ip_number(team[j]))
				return 0;
		}
	}
	return 1;
}

int main(object me, string arg)
{
	object env;
	string *fubenls,*txt,str;
	int i;
	mapping info;
	mixed *fbtime;
	object *team = me->query_team();
	int total,max,min;
	int lv, qi_lv, jing_lv, exp_lv, neili_lv, lv2;

	env = environment(me);
	if (!env||!(fubenls=FUBEN_D->query_where(base_name(env)))) return 0;

	if(!arg)
	{
		txt = ({});
		str = ZJOBLONG"������Ҹ����б�\n"ZJOBACTS2+ZJMENUF(2,2,9,30);
		for(i=0;i<sizeof(fubenls);i++)
		{
			if(mapp(info = FUBEN_D->query_info(fubenls[i])))
			{
				fbtime = localtime(info["time"]);

				txt += ({ HIM+info["cname"]+NOR"����"ZJBR+HIG+info["owner"]+NOR"-"
						+fbtime[2]+"-"+fbtime[1]+"-"+fbtime[0]+":fuben "+fubenls[i] });
			}
		}
		str += implode(txt,ZJSEP);
		write(str+"\n");
		return 1;
	}

	if(!mapp(info = FUBEN_D->query_info(arg)))
		return notify_fail("û�����������\n");

	if(info["owner"]!=me->query("id"))
		return notify_fail("�ⲻ����ĸ�����\n");
	
	if(sizeof(team)>info["team"])
		return notify_fail("�������������"+info["team"]+"�˽��룡\n");

	me->set_temp("fuben_path", arg);

	lv = to_int(pow(to_float(me->query("combat_exp")*10),0.333333333));
	qi_lv = me->query("max_qi");
	jing_lv = me->query("max_jing");
	neili_lv = me->query("max_neili");
	exp_lv = me->query("combat_exp");
	
	if (info["enter"]->query_temp("go_fuben")) 
		return notify_fail("���޷��ٴν������������\n");
	
	if (sizeof(team)>0) {
		if (sizeof(team) < 0)
			return notify_fail("̽��ʮ��Σ�գ�����Ŷ�����̫�١�\n");
		if (sizeof(team) > 5) 
			return notify_fail("̽���������˹��࣬����̫������ױ�¶��\n");
		if (team[0] != me) 
			return notify_fail("ֻ�ж��������ſ��Դ��ӽ���̽�ա�\n");
		
		if (!check_ip(team))
			return notify_fail("��Ķ�����ͬIP�齨���޷�����̽�ա�\n");
                        
		max = min = me->query("combat_exp");
		for (i = 0;i < sizeof(team);i ++)
		{
			if (!team[i])
				return notify_fail("��Ķ�����������⣬���ɢ�������齨��");
			if (!present(team[i], env))
				return notify_fail("��ô�����˲�ȫ����" + team[i]->query("name") + "��ôû����\n");
			if (team[i]->query_condition("killer"))
				return notify_fail("���ﲻ��ӭɱ�˿�ħ��"+team[i]->query("name")+"��ذɣ�"NOR"\n");
			if (me == team[i])
				continue;

			if (!interactive(team[i]))
				return notify_fail("�㻹�ǽ�" + team[i]->query("name") + "���������˰ɡ�\n");
                        
			total += team[i]->query("combat_exp");
			if (team[i]->query("combat_exp") > max)
				max = team[i]->query("combat_exp"); 
			if (team[i]->query("combat_exp") < min)
				min = team[i]->query("combat_exp");
		}
		if (min / (max / 100) < 50||(max-min)>2000000)
			return notify_fail("̽�չ���ʮ��Σ�գ����ǵľ�����̫���ˡ�\n");
		
			for (i = 0;i < sizeof(team);i ++)
			{
				lv2 = to_int(pow(to_float(team[i]->query("combat_exp")*10),0.333333333));
				if (lv2 > lv)
					lv = lv2;
				if (team[i]->query("max_qi") > qi_lv)
					qi_lv = team[i]->query("max_qi");
				if (team[i]->query("max_jing") > jing_lv)
					jing_lv = team[i]->query("max_jing");
				if (team[i]->query("max_neili") > neili_lv)
					neili_lv = team[i]->query("max_neili");
				if (team[i]->query("combat_exp") > exp_lv)
					exp_lv = team[i]->query("combat_exp");
			
				team[i]->move(info["enter"]);
				team[i]->set_temp("baozang/sk_lv", lv);//�趨������߼��ܵȼ�
				team[i]->set_temp("baozang/qi_lv", qi_lv);//�趨���������Ѫ
				team[i]->set_temp("baozang/jing_lv", jing_lv);//�趨���������Ѫ
				team[i]->set_temp("baozang/neili_lv", neili_lv);//�趨�����������
				team[i]->set_temp("baozang/exp_lv", exp_lv);//�趨������߾���
			} 
			info["enter"]->add_temp("go_fuben", 1);
	} else {
		me->move(info["enter"]);
		me->set_temp("baozang/sk_lv", lv);//�趨������߼��ܵȼ�
		me->set_temp("baozang/qi_lv", qi_lv);//�趨���������Ѫ
		me->set_temp("baozang/jing_lv", jing_lv);//�趨���������Ѫ
		me->set_temp("baozang/neili_lv", neili_lv);//�趨�����������
		me->set_temp("baozang/exp_lv", exp_lv);//�趨������߾���
		info["enter"]->add_temp("go_fuben", 1);
	}
	
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : fuben
 
���ָ�������ʾ��ǰ��������Ҹ�����
 
see also : score
HELP );
    return 1;
}


