// huangzhong-gong.c

inherit NPC;

void create()
{
	set_name("���ӹ�", ({ "huangzhong gong", "gong" }));
	set("title", "÷ׯ��ׯ��");
	set("long",
		"������÷ׯ��λׯ�����е�һ�Ļ��ӹ���\n"
		"��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
		"����������Ѯ������еȣ����ݺͰ����ס�\n");
	set("gender", "����");
	set("age", 62);
	set("class", "scholar");
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 28);
	set("int", 28);
	set("con", 28);
	set("dex", 28);

	set("max_qi", 4000);
	set("max_jing", 2000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 50);
	set("combat_exp", 1000000);

	set_skill("force", 200);
	set_skill("wuzheng-xinfa", 200);
	set_skill("dodge", 150);
	set_skill("piaoyibu", 150);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("wuyun-jianfa", 180);
	set_skill("literate", 150);

	map_skill("force", "wuzheng-xinfa");
	map_skill("dodge", "piaoyibu");
	map_skill("parry", "wuyun-jianfa");
	map_skill("sword", "wuyun-jianfa");
	setup();
	carry_object("/clone/weapon/changjian")->wield();
}
