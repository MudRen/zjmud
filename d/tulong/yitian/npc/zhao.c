#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
	set_name("����", ({ "zhao min", "min", "zhao"}));
	set("title", HIY "��Ԫ��������" NOR);
	set("long",
"��������ϼ����ɫ������ʮ������֮�У�����������Ӣ�������ֺ�̬��ͬ
ʱӺ�ݻ�������һ������֮�£�������Ȼ�𾴣����ұ��ӡ�\n");
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 30);
	set("str", 15);
	set("int", 25);
	set("con", 25);
	set("dex", 30);

	set("max_qi", 500);
	set("max_jing", 200);
	set("max_neili", 500);
	set("neili", 500);
	set("jiali", 50);
	set("combat_exp", 50000+random(10000));
	set("score", 20000);
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.ren" :),
	}) );

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("liangyi-jian", 80);
	set_skill("huifeng-jian", 80);
	set_skill("taiji-shengong", 90);
	set_skill("changquan", 80);
	set_skill("lingxu-bu", 80);
	map_skill("dodge", "lingxu-bu");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	map_skill("unarmed", "changquan");

	set("inquiry", ([
	    "���޼�" :  "�Ź���Զ�����أ���֪�������ɺã����䴺�������к��£�\n",
	    "���콣" :  "����Ϊ�����������ô������Ҫ��\n",
	]));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/female2-cloth")->wear();
}
void init()
{       
	object ob;
	ob = this_player();
	::init();

	add_action("do_get","get");
	add_action("do_yun","yun");
	add_action("do_yun","exert");

	remove_call_out("greeting");
	call_out("greeting", 1, ob);
}

int do_yun(string arg)
{
	object obj;

	obj=this_object();
	if (arg == "roar" )
	{
		message_vision(CYN "\n�����ȵ����޳����ӣ���������ɲ��������"NOR"\n",obj);
		return 1;
	}
	return 0;

}

int do_get(string arg)
{
	object obj, env, shelf;
	string what, where;

	if(!arg) 
	return 0;

	if(sscanf(arg,"%s from %s",what, where) !=2)
	return 0;

	obj=this_object();
	if(what == "yitian sword"||where == "shelf")
	{
		message_vision(CYN "\n�����ȵ����޳����ӣ��ݵ�����"NOR"\n",obj);

		message_vision(CYN "\n��������������������Ҫ��õ����콣Ҳ���ԣ���������"
				   "�ñ�Ӯ(bi)�ҵ����£�"NOR"\n",obj);
		return 1;
	}
	return 0;
}

int accept_fight(object who)
{
	command("say �۸�һ����СŮ����ʲô��Ҫ�Ⱥ��ҵ����±�(bi)��");
	return 0;
}

int accept_hit(object who)
{
	command("say �۸�һ����СŮ����ʲô��Ҫ�Ⱥ��ҵ����±�(bi)��");
	return 0;
}

int accept_kill(object who)
{
	command("say �۸�һ����СŮ����ʲô��Ҫ�Ⱥ��ҵ����±�(bi)��");
	return notify_fail("ɲ�Ǽ�������޴����֡�\n");
}

int accept_ansuan(object who)
{
	return notify_fail("����밵�㣬����ֻ��¥����Ӱ�ζ����������������\n");
}

void receive_damage(string type, int n)
{
	return;
}

void receive_wound(string type, int n)
{
	return;
}

void greeting(object ob)
{
	object env, shelf, sword;
	
	if( !ob || environment(ob) != environment() )
	return;

	if( !userp(ob))
	return;

	message_vision( HIW "$Nһ��¥����ֻ��һλ������Ů�������ã�������ϼ���绪������"+
			    "ʮ������֮�У�����������Ӣ�������ֺ�̬��ͬʱӺ�ݻ�������һ������֮�£�������Ȼ�𾴣����ұ��ӡ�\n"+
			    "��Ů���Ե�վ�ż��ˣ����Ÿ��죬���Ӽ��˵���̬�����ȿ�������һ�������ָ��֡�\n"+
			    "���ð���һ������ĺ�ľ�ƽ��ܣ������Ϻ����һ�������������Ľ����Ϻ�Ȼд�š�" NOR+HIY "����" NOR+HIW "�����֡�"NOR"\n",
			    ob,this_object());

	command("yi");
	command("say �ߣ����������������ҵ��˻��治�٣�");
	
	env = environment(this_object());
	shelf = present("shelf", env);
	sword = present("yitian sword", shelf);
		
	if (!sword) 
		message_vision(HIC "\n$Nҡ��ҡͷ��������ϧ���콣�Ѿ������������ˡ���"NOR"\n",
				   this_object());
}

