// huo.c

inherit NPC;

void create()
{
	set_name("������", ({"huo xiansheng", "huo", "xiansheng"}));
	set("long",
"��һ�����ݣ�����ί�����������Ժ�����˯����ģ����������������ʮ�������޿����ޡ�
ԭ�������Ƿ�ţ�ɵĴް�Ȫ��Ϊ�ܳ�������ڴˡ�\n"
	);

	set("gender", "����");
	set("attitude", "heroism");

	set("age", 51);
	set("shen_type", 0);
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 25);
	set("max_qi", 500);
	set("max_jing", 100);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 100);
	set("combat_exp", 100000);
	set("score", 100);
	set("apply/attack",  30);
	set("apply/defense", 30);

	set_skill("force", 50);
	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 50);
}
