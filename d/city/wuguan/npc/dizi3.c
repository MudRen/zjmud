//dizi3.c ���

#include <ansi.h>
inherit NPC;
string ask_me(object);

string* tools = ({
       __DIR__"obj/beixin",
       __DIR__"obj/armor",
       __DIR__"obj/junfu",
}); 

void create()
{
       set_name("���",({ "wan gui", "wan","gui" }) );
       set("title","�������������");
       set("gender", "����" );
       set("age", 26);
       set("long","��������ɽ�Ķ��ӣ���������������΢������������������\n");
       set("combat_exp", 4000);
       set("attitude", "friendly");

       set_skill("force", 30);
       set_skill("strike", 30);
       set_skill("sword", 30);

       set("inquiry", ([
              "����" : (: ask_me :),
       ]) );
       setup();

       set("huju_count", 10);       
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

string ask_me(string name)
{        
        object tool;

        if (present("armor", this_player()) || present("junfu",this_player()) || present ("pi beixin",this_player()))
            return RANK_D->query_respect(this_player())+"�㲻���Ѿ���Ҫ�������ˣ���ô����Ҫ�ˣ�����̰��Ŷ��";
 
        if (query("huju_count") < 1)
            return "��Ǹ�������ò���ʱ�򣬷����Ѿ������ˡ�";

        if (this_player()->query_temp("getarmor"))
            return RANK_D->query_respect(this_player())+"�㲻���Ѿ���Ҫ�������ˣ���ô����Ҫ�ˣ�����̰��Ŷ��";

        tool = new( tools[random(sizeof(tools))]);
        tool->set("value",10);
        tool->move(this_player());        
        this_player()->set_temp("getarmor", 1);
        add("huju_count", -1);
        message_vision("������$Nһ��"+tool->name()+"��\n", this_player());
        return "��ȥ�ɡ�����Ҫ��ס������ֻ�ɷ������䣬����ƾ�˷������ˡ�";
}     
 
void greeting(object ob)
{       
       command("bow "+ob->query("id"));
       command("say ��λ" + RANK_D->query_respect(ob)
                                + "������������� "HIY HBCYN"ask wan about ����"CYN" �ɡ�"NOR);
}                               
