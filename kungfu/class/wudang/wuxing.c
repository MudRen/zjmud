// wuxing.c ���е���

inherit NPC;

void create()
{
	set_name("���е���", ({ "wuxing dizi", "dizi", "wuxing"}));
	set("age", 23);
	set("gender", "����");
	set("long", "���佣������з�λ���ӡ�\n");
	set("attitude", "peaceful");
	set("str", 24);
	set("dex", 27);
	set("combat_exp", 420000);
	set("shen_type", 1);

	set_skill("unarmed", 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("force", 120);
	set_temp("apply/attack", 120);
	set_temp("apply/defense", 120);
	set_temp("apply/damage", 120);
	set_temp("apply/armor", 120);
	set("chat_chance", 2);
	set("chat_msg", ({
		"���е�������ߺ�ȣ����佣�����µ�һ��\n",
	}));
	create_family("�䵱��", 3, "����");
	setup();
	carry_object("/clone/weapon/changjian");
	carry_object("/d/wudang/obj/wuxingfu")->wear();
}
