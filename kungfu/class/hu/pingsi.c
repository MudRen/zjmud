// pingsi.c
#include <ansi.h>;

inherit NPC;
inherit F_GUARDER;

void create()
{
    set_name("ƽ��", ({"ping si", "ping"}));
    set("gender", "����");
    set("age", 65);
    set("long", "���Ǻ������Ĺ��������ۡ�\n");
    set("attitude", "peaceful");
    set("str", 20);
    set("int", 20);
    set("con", 24);
    set("dex", 20);

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("combat_exp", 150000);

    set_skill("force", 40);
    set_skill("blade", 40);
    set_skill("dodge", 40);
    set_skill("parry", 40);
    set_skill("unarmed", 40);

    create_family("�������", 0, "��Ӷ");

    set("inquiry",([
	"�ֻ�":     "�ֻ�... ���������\n",
	"��һ��":   "�ǣ����������ˣ�����\n",
	"���˷�":   "������ɲ��ǻ��ˡ�\n",
	"�԰�ɽ":   "�����Ҽ����˵Ľ�������û��˵�ġ� \n",
    ]));

    set("coagents", ({
	    ([ "startroom" : "/d/guanwai/xiaowu",
	       "id"	: "hu fei" ]),
    }));

    setup();

    set("title", "������Ӷ");
    carry_object("/clone/cloth/cloth")->wear();
}
