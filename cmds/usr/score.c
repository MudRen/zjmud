// score.c
#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);
string status_color(int current, int max);
string date_string(int date);
int shuxing(object ob,string arg);

mapping oprank = ([
	"��ʦ"     : HIW "��ʦ����  ",
	"�Ƿ��켫" : HIY "������",
	"��������" : HIY "�����  ",
	"��������" : HIR "�����  ",
	"¯����" : HIR "����    ",
	"���д��" : HIC "����    ",
	"��ͬ����" : HIC "���      ",
	"�������" : HIG "���      ",
	"���ֲ���" : HIG "��	",
	"����С��" : HIM "��	",
]);

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
	object ob;
	mapping my, special_skill,mci;
	int age, rmb, month,i;
	string line, str, race, skill_type,*skill_str;
	object weapon;
	int attack_points, dodge_points, parry_points;

	seteuid(getuid(me));
	if (! arg)
		ob = me;

	else if (wizardp(me))
	{
		ob = present(arg, environment(me));
		if (! ob || ! ob->is_character()) ob = find_player(arg);
		if (! ob || ! ob->is_character()) ob = find_living(arg);
		if (! ob || ! ob->is_character())
			return notify_fail("��Ҫ�쿴˭��״̬��\n");
	} else
		return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");

	my = ob->query_entire_dbase();
	mci = my["combat"];
	if (! mci) mci = ([ ]);

	if (playerp(ob) && (! stringp(my["born"]) || ! my["born"]))
		return notify_fail("��û�г����ţ��쿴ʲô��\n");

	if (my["max_jing"] < 1 || my["max_qi"] < 1)
		return notify_fail("�޷��쿴" + ob->name(1) + "��״̬��\n");
	line=ZJOBLONG;
	line += HIC "��" HIY "һһһһһһһһһһһһһһһһһһһһ" HIC "��"NOR"\n";
	line += sprintf( BOLD "  %s" NOR "\n  �ƺţ�%s\n",ob->short(1), RANK_D->query_rank(ob));

	if (playerp(ob))
	{
		age = ob->query("age");
		if (ob->query("gender") == "����")
			race = "����";
		else
			race = ob->query("gender");

		line += sprintf("  ���䣺%s��",chinese_number(age));
		if(ob->query("month"))
			line += sprintf("%s��",chinese_number(ob->query("month")));
		line += race + "��\n";
	}
	else
		line += sprintf(WHT "\n  ����һ%s%s���%s%s��\n",ob->query("unit"),chinese_number(ob->query("age")),ob->query("gender"),ob->query("race"));

	if (mapp(my["family"]))
	{
		if (my["family"]["master_name"])
			line += sprintf("  ʦ����%s��"NOR"\n",my["family"]["master_name"]);
		else
			line += "  ʦ��������"NOR"\n";
	} else
		line += "\n  ʦ��������"NOR"\n";
	line += sprintf(
		HIY " ����������[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" �����ԡ���[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" �����ǡ���[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")\n"+HIY" ��������[%i]"+HIG" (+%2d)"+GRN" (+"HIM"%2d"GRN")"NOR"\n", 
		my["str"],ob->query_str()-my["str"]-ob->query_temp("suit_eff/strength"),ob->query_temp("suit_eff/strength"),
		my["int"],ob->query_int()-my["int"]-ob->query_temp("suit_eff/intelligence"),ob->query_temp("suit_eff/intelligence"),
		my["con"],ob->query_con()-my["con"]-ob->query_temp("suit_eff/constitution"),ob->query_temp("suit_eff/constitution"),
		my["dex"],ob->query_dex()-my["dex"]-ob->query_temp("suit_eff/spirituality"),ob->query_temp("suit_eff/spirituality")
	);

	if (playerp(ob))
	{
		if (my["born_family"] && my["born_family"] != "û��")
		{
			line += HIW "  �������" + my["born_family"] +"�����ԡ�" + my["character"]+"��";
		}
		else if (stringp(my["born"]) && my["born"])
		{
			line += HIW "  ����" + my["born"] +"�����ԡ�" + my["character"]+"��";
		}
		else
			line += HIW "  ����δ����";

		skill_str=keys(ob->query("special_skill"));
		line +=HIG"\n  ����츳�����У�\n"NOR;
		for(i=0; i<sizeof(skill_str); i++)
		{
			line +=HIG" ��"+SPECIAL_D(skill_str[i])->name()+HIG"��\n";
		}

		if ((int)ob->query("zjvip/times") > 0)
			line += HIY "  ��Ļ�Աʱ�䣺"+CHINESE_D->chinese_time(ob->query("zjvip/times"))+ "��"NOR"\n";

		rmb = ob->query("rmb", 1);

		if ((int)ob->query("rmb") > 0)
			line += HIY "  ��Ŀǰ��ע���ʽ������" + chinese_number(rmb) + "Ԫ��"NOR"\n";

		if ((int)ob->query("yuanbao") > 0)
			line += HIY "  ��Ŀǰ��Ԫ����" + chinese_number(ob->query("yuanbao")) + "����"NOR"\n";

		if ((int)ob->query("balance") > 0)
			line += HIY "  ��Ŀǰ�Ĵ�" + MONEY_D->money_str((int)ob->query("balance")) + "��"NOR"\n";
		else
			line += HIY "  ��Ŀǰû�д�"NOR"\n";

		if (ob->query("gender") != "��1��")
		{
			if (! ob->query("couple/name"))
			{
				if (ob->query("gender") == "Ů��")
					line += HIC "  ����δ���䡣" NOR;
				else
					line += HIC "  ����δȢ�ޡ�" NOR;
			} else
				line += HIC "  ��İ�����" + ob->query("couple/name") + "(" +
					ob->query("couple/id") + ")��" NOR;
	
			if (! (int)ob->query("sex/times"))
			{
				if (ob->query("gender") == "Ů��")
					line += HIG "  ���Ǹ���Ů��" NOR;
				else
					line += HIC "  ���Ǹ�ͯ�С�" NOR;
			} 
			else
			{
				if (ob->query("gender") == "Ů��")
					line += HIG "  ���ѷǴ�Ů֮��" NOR;
				else
					line += HIC "  ���ѷ�ͯ��֮��" NOR;
			}

		}
	}

	if (playerp(ob))
	{
		if (! ((int)mci["MKS"] + (int)mci["PKS"]))
		{
			line += HIY "\n  �㵽ĿǰΪֹ��δ��ɱ�䡣";
		} else
		{
			line += sprintf(HIR "\n  �㵽ĿǰΪֹ�ܹ�ɱ��%s�Ρ�",chinese_number(mci["MKS"] + mci["PKS"]));
		}
	}

	if ((int)mci["dietimes"])
	{
		line += sprintf(HIR "\n  ���ܹ����ڰ��޳����ﴮ��%s�Ρ�"NOR"\n", chinese_number(mci["dietimes"]));
		line += sprintf(HIR "  �ϴ�������%s��"NOR"\n", ob->query("combat/last_die"));
		line += "";
	} else
	if (playerp(ob))

		line += HIC "\n  �㵽ĿǰΪֹ����������¼��"NOR"\n";

	while (playerp(ob))
	{
		string op;

		line += HIY "  �ζ�������   " NOR;
		if (my["breakup"])
			line += HIC "��" NOR;
		else
			line += HIR "��" NOR;

		line += HIY "		 ԪӤ������   " NOR;
		if (my["animaout"])
			line += HIC "��" NOR;
		else
			line += HIR "��" NOR;

		line += HIY "\n  �������أ�   " NOR;
		if (ob->query("relife/zhuanshi"))
			line += HIC "��" NOR;
		else
			line += HIR "��" NOR;

		line += HIY "		 ת��������   " NOR;
		if (ob->query("relife/zhuanshi"))
			line += HIC "��" NOR;
		else
			line += HIR "��" NOR;

		line += ""NOR"\n";
		break;
	}

	while (playerp(ob))
	{
		string op;
		if (ultrap(ob))
		{
			line += HIC "  �������Ѿ���Ϊ��ѧ����ʦ��"NOR"\n";
			break;
		}

		line += WHT "  ȭ�Ź���  " NOR;
		if (op = ob->query("opinion/unarmed"))
			line += oprank[op] + "	";
		else
			line += CYN "������	    ";

		line += NOR WHT " �������ã�  " NOR;
		if (op = ob->query("opinion/weapon"))
			line += oprank[op] + "	";
		else
			line += CYN "������";

		line += NOR WHT "\n  �ڼҹ���  " NOR;
		if (op = ob->query("opinion/force"))
			line += oprank[op] + "	";
		else
			line += CYN "������	    ";

		line += NOR WHT " ������  " NOR;
		if (op = ob->query("opinion/dodge"))
			line += oprank[op] + "	";
		else
			line += CYN "������";

		line += ""NOR"\n";
		break;
	}
	 line += sprintf(WHT "  ���������� " HIC "%7d\t    " NOR, my["score"]);
	 line += sprintf(WHT "  ���ɹ��ף� " HIW "%7d"NOR"\n", my["gongxian"]);

	if (playerp(ob))
	{
		line += sprintf(NOR + HIR "  ��    ���� " HIW "%7d\t    " NOR, my["total_hatred"]); 
		line += sprintf(WHT "  ���������� " HIC "%7d"NOR"\n", my["weiwang"]);
	}

	if (my["shen"] >= 0)
		line += sprintf(WHT "  ��    ���� " HIY "%7d\t    " NOR, my["shen"]);
	else
		line += sprintf(WHT "  а    ���� " HIR "%7d\t    " NOR, -ob->query("shen"));

	line += sprintf(HIM "  ��    �ۣ� %s%7d"NOR"\n",
			my["magic_points"] < 100 ? HIY : HIM,
		       (my["magic_points"] - my["magic_learned"]));

	line += HIC "��" HIY "һһһһһһһһһһһһһһһһһһһһ" HIC "��"NOR"\n";
	if (wiz_level(me) > 3) {
            line += HIG "  ���ף�"+HIM+ob->query("zjvip/all_pay")+NOR"\n";
	    if (ob->query("zjvip/master"))
               line += HIG "  ��ֵ������"+ob->query("zjvip/master")+NOR"\n";
            else
               line += HIG "  ��ֵ��������"NOR"\n";
		if (ob->query("birthday"))
			line += HIG "  ע��ʱ�䣺"+CHINESE_D->chinese_date(ob->query("birthday"),1)+NOR+"\n";
        }
	if (wiz_level(me) > 3) {
               line += HIG "  �������ԣ��ܼ�("+(ob->query("str")+ob->query("int")+ob->query("con")+ob->query("dex"))+")������+"+(ob->query("level")/10-ob->query("tianfu_point"))+"������+"+ob->query("gift/lighting")+"���Ե�+"+(ob->query("str")+ob->query("int")+ob->query("con")+ob->query("dex")-(ob->query("gift/lighting")+80+ob->query("level")/10-ob->query("tianfu_point")))+NOR"\n";
	       line += HIW "  �Ե�����������("+ob->query("gift/xiandan")+")��ϴ��("+ob->query("gift/xisuidan")+")�����("+ob->query("gift/unknowdan")+")������("+ob->query("gift/shenliwan")+")"NOR"\n";
             line += HIW "  �ϵ�����������("+ob->query("gift/xiandan_fail")+")��ϴ��("+ob->query("gift/xisuidan_fail")+")�����("+ob->query("gift/unknowdan_fail")+")������("+ob->query("gift/shenliwan_fail")+")"NOR"\n";
	       line += GRN "  �������ԣ���ò("+ob->query_per()+"/"+ob->query("per")+")����Դ("+ob->query("kar")+")"NOR"\n";
        }
	line = replace_string(line,"\n",ZJBR);
	if(line[(strlen(line)-4)..(strlen(line)-1)]=="$br#")
		line = line[0..(strlen(line)-5)];
	line += "\n";
	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	if (value > gift)
		return sprintf(HIY "%3d" NOR, value);
	else
	if (value < gift)
		return sprintf(CYN "%3d" NOR, value);
	else
		return sprintf("%3d", value);
}

string status_color(int current, int max)
{
	int percent;

	if (max) percent = current * 100 / max;
	else percent = 100;

	if (percent > 100) return HIC;
	if (percent >= 90) return HIG;
	if (percent >= 60) return HIY;
	if (percent >= 30) return YEL;
	if (percent >= 10) return HIR;
	return RED;
}

int help(object me)
{
	write(@HELP
ָ���ʽ�� score
	   score <��������>		   (��ʦר��)

���ָ�������ʾ���ָ������Ļ������ϡ�
���ָ��鿴״̬(hp)

HELP);
	return 1;
}
