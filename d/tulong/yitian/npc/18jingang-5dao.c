#include <ansi.h>
inherit NPC;
void create()
{
	set_name("��ɮ", ({ "dao seng", "dao", "seng"}) );
	set("long", "һ��ͺ�����У���¶�����������ʵ��\n"
		    "��������������µ�ʮ�˽��֮һ��\n");
	set("attitude", "heroism");
	set("title", "����������ʮ�˽��");
	set("nickname", HIR "�嵶���" NOR);
	set("age", 30);
	set("shen_type", -1);

	set("str", 10+random(20));
	set("int", 10+random(20));
	set("con", 10+random(20));
	set("dex", 10+random(20));
	
	set("max_qi", 2000);
	set("max_jing", 800);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 80);

	set("combat_exp", 200000+random(300000));
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "blade.xueyu" :),
		(: exert_function, "powerup" :),
	}) );


	set_skill("force", 120+random(20));
	set_skill("xuehai-mogong", 120+random(20));
	set_skill("dodge", 120+random(20));
	set_skill("shenkong-xing", 120+random(20));
	set_skill("cuff", 120+random(20));
	set_skill("yujiamu-quan", 120+random(20));
	set_skill("blade", 120+random(20));
	set_skill("xue-dao", 120+random(20));
	set_skill("parry", 120+random(20));
	set_skill("lamaism", 180);

	map_skill("force", "xuehai-mogong");
	map_skill("dodge", "shenkong-xing");
	map_skill("cuff", "yujiamu-quan");
	map_skill("parry", "xue-dao");
	map_skill("blade", "xue-dao");

	set_temp("apply/attack", 50+random(50));
	set_temp("apply/defense", 50+random(50));
	set_temp("apply/armor", 50+random(50));
	set_temp("apply/damage", 50+random(50));

	setup();

	carry_object("/d/beijing/npc/obj/jiasha")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}

void init()
{
	object ob;

	::init();

	ob = this_player();

	command("yi");
	command("say ��˭��ô�󵨣���Ȼ������������Ƥ����Ұ��\n");
	remove_call_out("kill_ob");
	call_out("kill_ob", 1, ob); 
}
