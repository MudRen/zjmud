// furen.c �Ϸ���

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("�Ϸ���", ({ "lao furen", "furen" }));
	set("long",  "������ȥ����Ѿ���С�ˣ�������ü������Ȼ�ɿ�������ķ��ˡ�\n");
	set("gender", "Ů��");
	set("age", 69);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 37);
	set("int", 32);
	set("con", 35);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 2500000);
	set("score", 10000000);

	set_skill("force", 270);
	set_skill("literate", 220);
	set_skill("unarmed", 260);
	set_skill("cuff", 270);
	set_skill("finger", 270);
	set_skill("strike", 260);
	set_skill("hand", 260);
	set_skill("claw", 260);
	set_skill("club", 260);
	set_skill("sword", 270);
	set_skill("blade", 260);
	set_skill("staff", 260);
	set_skill("dodge", 260);
	set_skill("parry", 270);
	set_skill("zihui-xinfa", 270);
	set_skill("douzhuan-xingyi", 270);
	set_skill("beidou-xianzong", 270);
	set_skill("canhe-zhi", 270);
	set_skill("qixing-quan", 270);
	set_skill("murong-sword", 270);

	map_skill("force", "zihui-xinfa");
	map_skill("dodge", "beidou-xianzong");
	map_skill("cuff",  "qixing-quan");
	map_skill("parry", "douzhuan-xingyi");
	map_skill("finger", "canhe-zhi");
	map_skill("sword", "murong-sword");

	prepare_skill("finger", "canhe-zhi");
	prepare_skill("cuff", "qixing-quan");

	create_family("Ľ������", 0, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.qixing" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "finger.lan" :),
		(: perform_action, "finger.zhi" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}
