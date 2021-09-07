// shuanger.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
int ask_go();
int ask_kiss();

void create()
{
	set_name("˫��", ({ "shuang er", "shuang","er"}));
	set("title", HIW "������˫" NOR);
	set("nickname", HIM "�󹦸��" NOR);
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 15);
	set("int", 25);
	set("con", 25);
	set("dex", 30);
	
	set("max_qi", 500);
	set("max_jing", 200);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 50);
	set("combat_exp", 50000+random(10000));
	set("score", 20000);

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("huashan-xinfa", 70);
	set_skill("huashan-quanfa", 70);
	set_skill("huashan-sword", 70);
	set_skill("feiyan-huixiang",80);
	map_skill("force", "huashan-xinfa");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "huashan-quanfa");
	map_skill("sword", "huashan-sword");
	map_skill("unarmed", "huashan-quanfa");

	set_temp("apply/attack", 15);
	set_temp("apply/attack", 15);
	set_temp("apply/damage", 15);
	set("inquiry", ([
	     "��Ը��Ը�������" : (: ask_go :),
	]));
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();
}


int ask_go()
{
	object me;
	string new_name,new_id,host_id;
	me=this_player();
	if(query("id")!="shuang er")
	{
		sscanf(query("id"),"%s's shuang er",host_id);
		if(query("id")==host_id)
		{
			say(query("name")+"�����۾����˿�"+
				me->query("name")+"��˵:��ȻԸ����,�Ҷ�����ġ�\n");
			return 1;
		}
		if(me->query("id")!=host_id)
		{
			say(query("name")+"�����۾����˿�"+
				me->query("name")+"��˵:���е�,�ҵ��������˵ġ�\n");
			return 1;
	   	}
	}
	if ((int)this_player()->query("weiwang")>=70)
	{
		write( HIY "˫����:���˴��Ҷ�����ɽ,���˶���ׯ�����д����"NOR"\n");
		write( HIY "����Ҫ�ҷ�������,��һ�����ġ�"NOR"\n");
		command("nod");	
		set_leader(me);
		new_name = me->query("name")+"��Ѿ��˫��";
		new_id=me->query("id")+"'s shuang er";
		set("name",new_name);
		set("id",new_id);
		set("long","����"+new_name+"��\n"
		"����һ��ʮ���������Ů,��Լʮ���������;\n"
		"һ��ѩ�׵�����,ü����С,Ц���绨,��Ц�����ؿ����㡣\n");
	}
	else say(query("name")+"�����۾�����"+
		me->query("name")+"��˵:���е�,����û��ͬ�⡣\n");
	return 1;
}

