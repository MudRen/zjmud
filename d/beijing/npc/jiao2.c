inherit NPC;

void create()
{
	set_name("ˤ����ͷ��", ({ "shuaijiao touling", "touling", "shuaijiao" }));
	set("long", 
		"һ�������������ˣ���Ŀ��࣬�����뺴��\n"
	      "���ǹ���ˤ����ͷ�죬���ڸ��൱���С�\n");
	set("gender", "����");
	set("age", 30);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 25);
	set("dex", 20);	
	set("max_qi", 500);
	set("max_jing", 500);
	set("neili", 100);
	set("max_neili", 100);

	set("combat_exp", 30000);

	set_skill("force", 70);
	set_skill("dodge", 70);
	set_skill("unarmed", 100);
	set_skill("parry", 70);

	setup();
}
