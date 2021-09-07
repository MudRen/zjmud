//dan_chongsu.c �������ܵ�

#include <ansi.h>

inherit ITEM;

int do_eat_2(string arg);

void create()
{
	set_name(HIR"�������ܵ�" NOR, ({ "chongsu dan"}) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һ�ź��ĵ�ҩ��ʹ�ú��ܹ����辭��ǿ�������ࡣ\n");
		set("value", 10000);
		set("no_drop",1);
		set("no_sell",1);
		set("yuanbao", 500);
		set("only_do_effect", 1);
		set("unit", "��");
	}
}

void init()
{
	add_action("do_eat_2","chongsujm");
}

int do_eat_2(string arg)
{
	object ob,me=this_player();		
	string msg, jingmai, dan, skill, *yin, *yang;
	int i;

	if(!arg||arg=="")
	{
		tell_object(me, ZJOBLONG + "��ѡ������"NOR+"\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+
					CYN"������"NOR":chongsujm ������"ZJSEP+
					CYN"������"NOR":chongsujm ������\n");
		return 1;
	}

	yang = ({"sword","blade","whip","staff","throwing","unarmed","strike","cuff","finger","hand","leg"});
	yin = ({"force","dodge","parry"});

	if (sscanf(arg, "%s for %s", jingmai, skill) == 2)
	{
		if (jingmai !="������" && jingmai !="������") {
			tell_object(me, "����ѡ�����\n");
			return 1;
		}
		if(jingmai == "������")
		{
			if(me->query("meridian/ap")==skill)
			{
				tell_object(me, "��Ŀǰǿ������ʽ����ܣ��������ܾ�����\n");
				return 1;
			}
			else if(member_array(skill,yang)==-1)
			{
				tell_object(me, "����Ĳ�����\n");
				return 1;
			}
			else
				me->set("meridian/ap",skill);
		}
		else if(jingmai == "������")
		{
			if(me->query("meridian/dp")==skill)
			{
				tell_object(me, "��Ŀǰǿ������ʽ����ܣ��������ܾ�����\n");
				return 1;
			}
			else if(member_array(skill,yin)==-1)
			{
				tell_object(me, "����Ĳ�����\n");
				return 1;
			}
			else
				me->set("meridian/dp",skill);
		}
	}
	else
	{
		msg = "��ѡ����Ҫ����ǿ���ļ������ͣ�\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		if(arg == "������")
			msg += 	"����:chongsujm "+arg+" for sword"ZJSEP
				"����:chongsujm "+arg+" for blade"ZJSEP
				"�޷�:chongsujm "+arg+" for whip"ZJSEP
				"�ȷ�:chongsujm "+arg+" for staff"ZJSEP
				"����:chongsujm "+arg+" for throwing"ZJSEP
				"ȭ��:chongsujm "+arg+" for unarmed"ZJSEP
				"�Ʒ�:chongsujm "+arg+" for strike"ZJSEP
				"ȭ��:chongsujm "+arg+" for cuff"ZJSEP
				"ָ��:chongsujm "+arg+" for finger"ZJSEP
				"�ַ�:chongsujm "+arg+" for hand"ZJSEP
				"�ȷ�:chongsujm "+arg+" for leg";
		else if(arg == "������")
			msg += 	"�Ṧ:chongsujm "+arg+" for dodge"ZJSEP
				"�м�:chongsujm "+arg+" for parry"ZJSEP
				"�ڹ�:chongsujm "+arg+" for force";
		else
			msg = "��Ҫ����ʲô������";
		tell_object(me, ZJOBLONG +msg+ "\n");
		return 1;
	}

	tell_object(me, "��һ������������һ��" + name() +"��ֻ��һ�������ӵ���ֱ����𣬾���ȫ�������ֻص����"NOR"\n��ϲ�������ܾ����ɹ���\n");
	
	destruct(this_object());

	return 1;
}

int do_effect(object me)
{
	do_eat_2("");
	return 1;
}

int query_autoload() { return 1; }
