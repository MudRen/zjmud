#include <ansi.h>
inherit ITEM;
string *b_names = ({

  "ϸ��ĺ�",
  "ϸ�����",
  "ϸ�����",
  "ϸ�����",
  "ϸ��Ļ�",
  "ϸ�����",
  "ϸ��ĳ�",
  "�ֲڵĺ�",
  "�ֲڵ���",
  "�ֲڵ���", 
  "�ֲڵ���", 
  "�ֲڵĻ�", 
  "�ֲڵ���", 
  "�ֲڵĳ�",  
  "��׼�ĺ�",
  "��׼����",
  "��׼����",
  "��׼����",
  "��׼�Ļ�",
  "��׼����",
  "��׼�ĳ�",
  "���µĺ�",
  "���µ���",
  "���µ���",
  "���µ���",
  "���µĻ�",
  "���µ���",
  "���µĳ�",
  "�����ĺ�",
  "��������",
  "��������",
  "��������",
  "�����Ļ�",
  "��������",
  "�����ĳ�",
});

mapping names = ([
  "ϸ��ĺ�":       "broken red",
  "ϸ�����":       "broken blue",
  "ϸ�����":       "broken green",
  "ϸ�����":       "broken cyan",
  "ϸ��Ļ�":       "broken yellow",
  "ϸ�����":       "broken purple",
  "ϸ��ĳ�":       "broken orange",
  "�ֲڵĺ�":       "crude red",
  "�ֲڵ���":       "crude blue",
  "�ֲڵ���":       "crude green",
  "�ֲڵ���":       "crude cyan",
  "�ֲڵĻ�":       "crude yellow",
  "�ֲڵ���":       "crude purple",
  "�ֲڵĳ�":       "crude orange",
  "��׼�ĺ�":       "standard red",
  "��׼����":       "standard blue",
  "��׼����":       "standard green",
  "��׼����":       "standard cyan",
  "��׼�Ļ�":       "standard yellow",
  "��׼����":       "standard purple",
  "��׼�ĳ�":       "standard orange",
  "���µĺ�":       "delicate red",
  "���µ���":       "delicate blue",
  "���µ���":       "delicate green",
  "���µ���":       "delicate cyan",
  "���µĻ�":       "delicate yellow",
  "���µ���":       "delicate purple",
  "���µĳ�":       "delicate orange",
  "�����ĺ�":       "perfect red",
  "��������":       "perfect blue",
  "��������":       "perfect green",
  "��������":       "perfect cyan",
  "�����Ļ�":       "perfect yellow",
  "��������":       "perfect purple",
  "�����ĳ�":       "perfect orange",
]);

void setname()
{


    int i, j,k;

    string name,*kn,*id;

if (query("reward_lvl")>0) {
i=(query("b_lvl")-1)*7+query("reward_lvl")-1;
j=query("reward_lvl")-1;
}

if ( query("reward_lvl")<1){
k=random(1000);
       if(k>995){
        i=21+random(7);
        j=i-21;
        set("is_monitored", 1);
      }
else if(k>960){
        i=14+random(7);
        j=i-14;
        set("is_monitored", 1);
      }
else if(k>800){
        i=7+random(7);
        j=i-7;
        set("is_monitored", 1);
      }
else { i=random(7);
         j=i;}
}

     set("b_lvl",i/7+1);

        
    name=b_names[i]+"��ʯ";
    set("baoshi",b_names[i]);
    id=({names[b_names[i]]+" baoshi","baoshi"});
    set("reward_lvl",j+1);
    if(j==0){
    set_name(HIR+name+NOR,id); }
    if(j==1){
    set_name(HIB+name+NOR,id); }
    if(j==2){
    set_name(HIG+name+NOR,id); }
    if(j==3){
    set_name(HIC+name+NOR,id); }
    if(j==4){
    set_name(HIY+name+NOR,id); }
    if(j==5){
    set_name(HIM+name+NOR,id); }
    if(j==6){
    set_name(YEL+name+NOR,id); }
    if(j==7){
    set_name(YEL+name+NOR,id); }
}


void changename(object ob,int i)
{
    int j,k;
    string name,*id;
        i=i-1;

if(i>=28){
        j=i-28;
        ob->set("is_monitored", 1);
      }
else if(i>=21){
        j=i-21;
        ob->set("is_monitored", 1);
      }
else if(i>=14){
        j=i-14;
       ob->set("is_monitored", 1);
      }
else if (i>=7){
        j=i-7;
        ob->set("is_monitored", 1);
      }
else {  j=i;}

     ob->set("b_lvl",i/7+1);

    
    name=b_names[i]+"��ʯ";

    id=({names[b_names[i]]+" baoshi","baoshi"});

    ob->set("baoshi",b_names[i]);

    ob->set("reward_lvl",j+1);
    if(j==0){
    ob->set_name(HIR+name+NOR,id); }
    if(j==1){
    ob->set_name(HIB+name+NOR,id); }
    if(j==2){
    ob->set_name(HIG+name+NOR,id); }
    if(j==3){
    ob->set_name(HIC+name+NOR,id); }
    if(j==4){
    ob->set_name(HIY+name+NOR,id); }
    if(j==5){
    ob->set_name(HIM+name+NOR,id); }
    if(j==6){
    ob->set_name(YEL+name+NOR,id); }
    if(j==7){
    ob->set_name(YEL+name+NOR,id); }
}


void create(int i)
{
	setname();
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 2000000);
		set("unit","��");
		set("color", HIM);  //HIB
		set("no_sell",1);
		set("long",HIM"һ�鷢����������ı�ʯ����˵��Ů洲���ʯ�����,Ҳ��֪��ʲôʱ�����뷲��ġ�\n"NOR);
	}
	setup();
}


void init()
{
    add_action("do_enchase", "enchase");
    add_action("do_enchase", "inset");
    add_action("do_combine", "combine");
}


int do_enchase(string arg)
{
   object in_obj;
   string item,str,mats;
   int rd,inset_num ,i,j,k;
   object me = this_player();
   object ob = this_object();

   if(!arg) return notify_fail("��Ҫ��ʲô��\n");



   if(sscanf(arg, "%s", item)!=1) return notify_fail("��Ҫ�ѱ�ʯ��Ƕ��ʲô�ϣ�\n");


   if(!objectp(in_obj = present(item, me))) return notify_fail("������û������������\n");

   if( in_obj->query("equipped") )
      return notify_fail("����������������������Ƕ��ʯ��\n");
//added by wuyou,lest one player inset baoshi in another player
   if( in_obj->is_character() )
      return notify_fail("���ѵ����ˣ���ô�ܰѱ�ʯ��Ƕ�������ϣ�\n");
//   if( in_obj->query("no_zm")||in_obj->query_unique())
//      return notify_fail("���װ��������Ƕ��ʯ��\n");
   i=ob->query("b_lvl")*7;
    if(i>28) k=15;
    else if(i>21) k=10;
    else if(i > 14) k=6;
    else if(i > 7) k=3;
    else k=1;
   j=ob->query("reward_lvl");
   mats = in_obj->query("material");       //װ��������
   inset_num = in_obj->query("inset_num");  // Ƕ�˼�����
   if(!inset_num) inset_num = 1;
   else inset_num = inset_num + 1;
   if(inset_num > 5) return notify_fail(in_obj->query("name")+"���Ѿ���Ƕ��̫��ı�ʯ��!\n");

   if(!in_obj->query("weapon_prop/damage"))   //����
  {     message_vision(CYN"$N��$n"+CYN"��Ƕ��"+in_obj->query("name")+CYN"�� \n"NOR,me,ob);
       tell_room(environment(me),HIG"ֻ��"+ob->name()+HIG"����һ�Ų��õĽ��,������"+in_obj->query("name")+HIG"����Χ \n"NOR);
 //�ж�ͬ�౦ʯ
       if(j==1){
       in_obj->add("armor_prop/armor",k*2);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
        }
       if(j==2){
       in_obj->add("armor_prop/strength",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��������ˣ�\n"NOR,me);
        }
       if(j==3){
       in_obj->add("armor_prop/qi",k*10);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
        }
       if(j==4){
       in_obj->add("armor_prop/dexerity",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�����ӯ�ˣ�\n"NOR,me);
         }
       if(j==5){
       in_obj->add("armor_prop/dodge",k*2);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ����������ԣ�\n"NOR,me);
        }
       if(j==6){
       in_obj->add("armor_prop/intelligence",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�����ӯ�ˣ�\n"NOR,me);
        }
       if(j==7){
       in_obj->add("armor_prop/constitution",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
        }

     //  me->add("bellicosity",1000);
       in_obj->set_weight(in_obj->query_weight()+500);
       in_obj->set("inset_num",inset_num);
       in_obj->set("no_sell",1);
       in_obj->add("inset_b",inset_num);  //װ��b
       in_obj->set("name",HIG+in_obj->query("name")+NOR);

       if(!in_obj->query("old_long"))
         in_obj->set("old_long",in_obj->query("long"));

       if(!in_obj->query("old_ee"))
          in_obj->set("old_ee",ob->query("name"));

     else in_obj->set("old_ee",in_obj->query("old_ee")+" "+ob->query("name"));

       in_obj->set("long",in_obj->query("old_long")+"������Ƕ��"+HIW+chinese_number(inset_num)+"�ű�ʯ��"+in_obj->query("old_ee")+"��\n"NOR);

       in_obj->save();
       destruct(ob);
       return 1;
}

else{
//����
        message_vision(CYN"$N��$n"+CYN"��Ƕ��"+in_obj->query("name")+CYN"�� \n"NOR,me,ob);
       tell_room(environment(me),HIG"ֻ��"+ob->name()+HIG"����һ�Ų��õĽ��,������"+in_obj->query("name")+HIG"����Χ \n"NOR);

       if(j==1){
       in_obj->add("weapon_prop/damage",k*2);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��������ˣ�\n"NOR,me);
        }
       if(j==2){
       in_obj->add("weapon_prop/strength",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��������ˣ�\n"NOR,me);
        }
       if(j==3){
       in_obj->add("weapon_prop/qi",k*10);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
        }
       if(j==4){
       in_obj->add("weapon_prop/dexerity",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�����ӯ�ˣ�\n"NOR,me);
         }
       if(j==5){
       in_obj->add("weapon_prop/dodge",k*2);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø�����ӯ�ˣ�\n"NOR,me);
        }
       if(j==6){
       in_obj->add("weapon_prop/intelligence",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ����������ԣ�\n"NOR,me);
        }
       if(j==7){
       in_obj->add("weapon_prop/constitution",k);
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);
        }

       if(k>20) {
       in_obj->set("material","diamond");
       message_vision(CYN""+in_obj->query("name")+CYN"�ƺ���ø��Ӽ�ʵ�ˣ�\n"NOR,me);}


       in_obj->set_weight(in_obj->query_weight()+500);
       in_obj->set("no_sell",1);
       in_obj->set("inset_num",inset_num);
       in_obj->add("inset_b",inset_num);  //װ��g
       in_obj->set("name",HIG+in_obj->query("name")+NOR);

       if(!in_obj->query("old_long"))
         in_obj->set("old_long",in_obj->query("long"));

       if(!in_obj->query("old_ee"))
          in_obj->set("old_ee",ob->query("name"));

     else in_obj->set("old_ee",in_obj->query("old_ee")+" "+ob->query("name"));

       in_obj->set("long",in_obj->query("old_long")+"������Ƕ��"+HIW+chinese_number(inset_num)+"�ű�ʯ��"+in_obj->query("old_ee")+"��\n"NOR);
       in_obj->save();
       destruct(ob);
       return 1;
}

  return notify_fail("����Ƕ��ʯʧ���ˣ�\n");
}




int do_combine(string arg)
{

   int i,j;
    string name,*kn,*id;

   object me = this_player();
   object ob = this_object();
object ob2,ob3;

i=ob->query("b_lvl");
j=ob->query("reward_lvl")-1;

	if (!arg || arg == "")
		return notify_fail("����ϲ�ʲô��ʯ��\n");
	if (arg != ob->query("id")) return 0;
	if (ob->query("b_lvl") == 5)
		return notify_fail("�����ʯ�Ѿ�����ߵȼ��ˣ�\n");
	if (me->query("max_neili") < 500 || me->query("neili") < 800)
		return notify_fail("�������ڵ�������Ϊ�����޷��˹��ϲ���ʯ��\n");

//	ob = present(ob->query("id"), me);
	if ( !objectp(ob2= present(ob->query("id")+" 2", me)) )
		return notify_fail("�����������"+ob->query("name")+"���ϲ���\n");
	if ( !objectp(ob3= present(ob->query("id")+" 3", me)) )
		return notify_fail("�����������"+ob->query("name")+"���ϲ���\n");

if (random(100)>24){
				message_vision(HIM"$N������"+ob->query("name")+HIM"����һ�𣬰�����������������"+ob->query("name")+HIM"�����������......\n"HIG"������$N�ջ���������"+ob->query("name")+HIG"�ƺ���ø��������ˣ�\n"NOR, me);
				me->add("max_neili", -10);
				me->add("neili", -500);
				me->start_busy(1);
	destruct(ob2);
	destruct(ob3);
	                  ob->set("b_lvl",i+1);

i=i*7+j;
    name=b_names[i]+"��ʯ";
    set("baoshi",b_names[i]);
    id=({names[b_names[i]]+" baoshi","baoshi"});

j=ob->query("reward_lvl")-1;

    if(j==0){
    set_name(HIR+name+NOR,id); }
    if(j==1){
    set_name(HIB+name+NOR,id); }
    if(j==2){
    set_name(HIG+name+NOR,id); }
    if(j==3){
    set_name(HIC+name+NOR,id); }
    if(j==4){
    set_name(HIY+name+NOR,id); }
    if(j==5){
    set_name(HIM+name+NOR,id); }
    if(j==6){
    set_name(YEL+name+NOR,id); }
    if(j==7){
    set_name(YEL+name+NOR,id); }

				return 1;
			
		}

	else {				message_vision(HIM"$N������"+ob->query("name")+HIM"����һ�𣬰�����������������"+ob->query("name")+HIM"�����������......\n"HIW"ֻ�����ǡ���һ�����죬$N���е�"+ob->query("name")+HIW"��÷��飡\n"NOR, me);

	destruct(ob2);
	destruct(ob3);
	destruct(ob);
			return 1;
   }
}

int query_autoload() { return 1; }
