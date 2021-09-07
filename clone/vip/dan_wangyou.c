//bianxingdan.c ���Ե�

#include <ansi.h>

inherit ITEM;

int do_eat_2(string arg);

void create()
{
	set_name(HIR"���ǵ�" NOR, ({ "wangyou dan"}) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һ��ѩ�׵ĵ�ҩ����˵ʹ�ú��ܹ��ı��Լ����Ը�\n");
		set("value", 10000);
		set("no_sell",1);
		set("no_shop",1);
		set("yuanbao", 600);
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
		tell_object(me, ZJOBLONG + "��ȷ��Ҫ���Ը��Ϊ��"NOR+"\n"ZJOBACTS2+ZJMENUF(2,2,10,30)+
					CYN"��������"NOR":bianxing �������� wangyou dan"ZJSEP+
					CYN"������"NOR":bianxing ������ wangyou dan"ZJSEP+
					CYN"�ĺ�����"NOR":bianxing �ĺ����� wangyou dan"ZJSEP+
					CYN"���ռ�թ"NOR":bianxing ���ռ�թ wangyou dan\n");
		return 1;
	}

	if( !objectp(ob = present(id, me)) )
		return 0;	
	
	family = me->query("family/family_name");
/*
	if (	family == "������" 
	|| family == "������" 
	|| family == "���չ�"
	|| family == "ѩɽ��"
	|| family == "������" ) {
		tell_object(me, "�㻹û�г�Ϊ����ʦ���޷�ʹ��" + name() +"��\n");
		return 0;
	}
*/
	if (gender !="��������" && gender !="������" && gender !="�ĺ�����" && gender !="���ռ�թ") {
		tell_object(me, "û�������Ը�\n");
		return 1;
	}
		
	if(me->query("character") == gender)
	{
		tell_object(me,sprintf("����Ը�������%s��\n", gender));
		return 1;
	}
	
	tell_object(me, "��һ������������һ��" + name() +"��\n");

	me->set("character", gender);
	tell_object(me,"����Ը�ɹ���Ϊ"+gender+"��\n");
	
	if (gender != "��������") {
		skill += ({"jiuyin-shengong",});
	}
	if (gender != "������") {
		skill += ({"never-defeated",});
	}
	if (gender != "�ĺ�����") {
		skill += ({"bluesea-force",});
	}
	if (gender != "���ռ�թ") {
		skill += ({"kuihua-mogong",});
	}

	if (sizeof(skill) > 0) {
		for (i = 0; i < sizeof(skill); i++) {
			if (me->query_skill(skill[i], 1)) {
				tell_object(me, "�����Ը񲻷�������ʹ������ "+me->query_skill(skill[i], 1)+" �� "+to_chinese(skill[i])+" ��\n");
				me->delete_skill(skill[i]);

			}
		}
	}
	CHANNEL_D->do_channel( this_object(), "rumor","��˵"+me->query("name")+"������һ��"+name()+""HIM"���Ը��䣬��Ϊ��"+gender+"��");
	me->save();
	log_file("static/using", sprintf("%s(%s) eat ���ǵ� ��Ϊ %s ʱ�䣺%s.\n",
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
