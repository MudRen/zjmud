// rong.c ����

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({"huang rong", "huang", "rong"}));
	set("title", "�һ�����������Ů");
	set("gender", "Ů��");
	set("age", 18);
	set("long", @LONG
�����һ������Ķ���Ů�������ڵ����������������������Ů�������۰���
���������ѷ��ϲ���Ĵ����ܡ�
LONG );

    set("attitude", "peaceful");
    set("class", "scholar");
	
    set("str", 18);
    set("int", 36);
    set("con", 21);
    set("dex", 26);

    set("qi", 800);
    set("max_qi", 800);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 1000);
    set("max_neili", 1000);
    set("jiali", 0);
	
    set("combat_exp", 200000);
    set("score", 100000);
	
    set_skill("force", 80);
    set_skill("bibo-shengong", 80);
    set_skill("luoying-xinfa", 80);
    set_skill("unarmed", 80);
    set_skill("xuanfeng-leg", 80);      // ����ɨҶ��
    set_skill("strike", 80);	    // �����Ʒ�
    set_skill("luoying-shenzhang", 80);
    set_skill("dodge", 150);
    set_skill("anying-fuxiang", 100);
    set_skill("parry", 85);
    set_skill("literate",180);	   // ����ʶ��
    set_skill("sword", 80);
    set_skill("luoying-shenjian",80);

    map_skill("force"  , "bibo-shengong");
    map_skill("unarmed", "xuanfeng-leg");
    map_skill("strike" , "luoying-zhang");
    map_skill("dodge"  , "anying-fuxiang");
    map_skill("sword"  , "luoying-shenjian") ;
	
    create_family("�һ���", 2, "����");

    set("inquiry", ([
	"��ҩʦ" : "����ѽ, ����������? ",
	"����"   : "��ô? �����Ҿ�������Ϣ��? ",
    ]));

    setup();
    carry_object("/d/taohua/obj/ruanwei")->wear();
    carry_object("/d/taohua/obj/shudai")->wear();
}

