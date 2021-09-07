//dizi5.c ��ԫ by river

inherit NPC;

#include <ansi.h>
void create()
{
        set_name("��ԫ", ({ "bo yuan", "bo", "yuan"}));
        set("title","������������");
        set("long", "��������ɽ������ӣ����ʱ��һ�㲻����������ˡ�\n");
        set("gender", "����");
        set("age", 24);
        set("combat_exp", 4500);
        set("shen_type", 1);

        set_skill("literate", 30);
        set_skill("force", 45);
        set_skill("strike", 45);
        set_skill("sword", 45);
 
        setup();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int prevent_learn(object ob, string skill)
{
        if (skill == "literate")
                return 0;
        return 1;
}

int is_apprentice_of(object ob)
{
        return 1;
}

int recognize_apprentice(object ob)
{
        int money=20, level = ob->query_skill("literate", 1);

        if (level>10) money=10;
        if (level>20) money=20;
        if (level>30) money=50;  

        ob->delete_temp("mark/literate");
        switch(MONEY_D->player_pay(ob, money)){
                case 0:
                case 2:
                return notify_fail("������ѧϰһ������Ҫ�ķ�����"+MONEY_D->money_str(money)+"�������ϴ�����Ǯ�����ˡ�\n");
        }
        ob->set_temp("mark/literate", 1);
        return 1;
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if ( ob->query_skill("literate") >= 30 ) return;
        command("hi " + ob->query("id"));
        command("say ��λ" + RANK_D->query_respect(ob)+ "����˵����ȶ�����Ҫ������Ŀ��ʶ�������ȥ�����\n"+
                "Щ�书�ؼ��أ�����Ը���ѧ�����д�� "HIY HBCYN"xue bo literate"CYN" ��"NOR);
}
