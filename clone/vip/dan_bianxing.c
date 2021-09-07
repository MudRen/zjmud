//bianxingdan.c ���Ե�

#include <ansi.h>

inherit ITEM;

int do_eat_2(string arg);

void create()
{
	set_name(HIR"���Ե�" NOR, ({ "bianxing dan"}) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һ�ź��ĵ�ҩ����˵ʹ�ú��ܹ��ı��Լ����Ա�\n");
		set("value", 10000);
		set("no_sell",1);
		set("yuanbao", 400);
		set("only_do_effect", 1);
		set("unit", "��");
	}
}

void init()
{
	add_action("do_eat_2","bianxing");
}

int do_eat_2(string arg)
{
	object ob,me=this_player();		
	string gender, id, family;
	string *skill=({});
	int i;
	
	if (!arg||sscanf(arg,"%s %s", gender, id) != 2)
	{
		tell_object(me, ZJOBLONG + "��ȷ��Ҫ����Ϊ��"NOR+"\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+
					CYN"����"NOR":bianxing ���� bianxing dan"ZJSEP+
					CYN"Ů��"NOR":bianxing Ů�� bianxing dan"ZJSEP+
					CYN"����"NOR":bianxing ���� bianxing dan\n");
		return 1;
	}

	if( !objectp(ob = present(id, me)) )
		return 0;	
	
	family = me->query("family/family_name");

	if (	family == "������" 
	|| family == "������" 
	|| family == "���չ�"
	|| family == "ѩɽ��"
	|| family == "������" ) {
		tell_object(me, "���޷�ʹ��" + name() +"��\n");
		return 0;
	}
	if (gender !="����" && gender !="Ů��" && gender !="����") {
		tell_object(me, "û�������Ա�\n");
		return 1;
	}
		
	if(me->query("gender") == gender)
	{
		tell_object(me,sprintf("���ѱ�������%s��\n", gender));
		return 1;
	}
	
	tell_object(me, "��һ������������һ��" + name() +"��\n");

	me->set("gender", gender);
	tell_object(me,"��ɹ���Ϊ"+gender+"��\n");
	
	if (gender != "����") {
		skill += ({"anran-zhang",});
	}
	if (gender != "����") {
		skill += ({"pixie-jian",});
	}
	if (gender != "Ů��") {
		skill += ({"yuenv-jian",});
	}
	if (gender == "����") {
		skill += ({"yijinjing",});
	}

	if (sizeof(skill) > 0) {
		for (i = 0; i < sizeof(skill); i++) {
			if (me->query_skill(skill[i], 1)) {
				tell_object(me, "�����Ա𲻷�������ʹ������ "+me->query_skill(skill[i], 1)+" �� "+to_chinese(skill[i])+" ��\n");
				me->delete_skill(skill[i]);

			}
		}
	}
	CHANNEL_D->do_channel( this_object(), "rumor","��˵"+me->query("name")+"������һ��"+name()+""HIM"�������"+gender+"��");
	me->save();
	log_file("static/using", sprintf("%s(%s) eat ���Ե� at %s ʱ�䣺%s.\n",
				me->name(1), me->query("id"), gender, ctime(time())));
	destruct(this_object());

	return 1;
}

int do_effect(object me)
{
	do_eat_2("");
	return 1;
}

int query_autoload() { return 1; }
