// magic-beast.h

/************************************************************
 * ħ���������������Ϊ�����ڡ������ڡ��ɳ��ڡ���̬�ںͳ����ڡ�
 * �����ڣ�����������ħ�������ԣ���ľˮ��������ʱ��һ���£�
 * �ɳ��ڣ����޻���帽�����������ϣ������������˵�����������
 *	 �ṩ����������Խ�࣬���޳ɳ�Խ�죬ͬʱ�����ҲԽǿ��
 *	 ������ħ��ֵ��ʱ��ʮ���£�
 * ��̬�ڣ���̬�ڵĻ����ǻ���һ�����������ʱ�ڣ���һʱ�ڵĻ�
 *	 �޻����ɳɳ����������˹�����������ʱ��һ���£�
 * �����ڣ��������Ľ׶γ����ھ���ʵ���ڣ���������Ϊ���߸���
 *	 ���������ϣ��������ˡ�
 * ���������ľ�������ˮ�����䡢������ȡ����ĺ�ʵ��
 ************************************************************/
 
#include <ansi.h>
#include <name.h>
#include <command.h>
#include <combat.h>

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_UNIQUE;

int is_item_make() { return 1; }
int is_magic_beast() { return 1; }
int is_stay_in_room() { return 1; }

mapping types = ([
	"gold"  : "�������",
	"wood"  : "ľ�����",
	"water" : "ˮ������",
	"fire"  : "�������",
	"soil"  : "���ĺ�ʵ",
]);

string chinese_s(mixed arg)
{
      if (! stringp(arg)) return "��";
      if (arg == "gold")  return HIY "��";
      if (arg == "wood")  return WHT "ľ";
      if (arg == "water") return HIG "ˮ";
      if (arg == "fire")  return HIR "��";
      if (arg == "soil")  return YEL "��";
}

nosave int last_age_set = 0;

void create()
{
	set_name("ħ����", ({ "magic beast" }));
	set("long", "��ҿ���������ȥָ���ĵط�(rideto)��\n");	
	set("race", "Ұ��");
	set("unit", "ֻ"); 
	set("str", 30);
	set("int", 30);
	set("spi", 30);
	set("con", 30);
	set("dex", 30);
	set("no_sell", "����ҲҪ���������ǵ���������Ѫ֮��Լ��"); 
	set("owner", "diyu");
	set("owner_name", "����ʹ��");
	set("limbs", ({ "ͷ��", "����", "ǰ��", "�ᱳ", "β��" }) );
	set("verbs", ({ "bite", "hoof" }) );
	
	set("qi", 300);
	set("max_qi", 300);
	set("jing", 100);
	set("max_jing", 100);
	set("neili", 100);
	set("max_neili", 100);    
	set("jingli", 100);
	set("max_jingli", 100);		 
	set("shen_type", 0);
	set("combat_exp", 50000);
	set("attitude", "peaceful"); 
	set("obedience", 2);   

	set_temp("apply/attack", 50);
	set_temp("apply/damage", 50);
	set_temp("apply/defence",50);
	set_temp("apply/armor", 50);
	
	if (! check_clone()) return 0;
	
	setup();
	::restore();
	keep_heart_beat(); 
}

string long()
{
	string result;
	string level;
	
	result = query("long");

	if (! query("magic/owner"))
	{
		result += HIW "��Ŀǰ�����������ڣ�˿��������������ħ�����ԡ�"NOR"\n";
		return result;
	} else
	{
		if (! query("magic/growup"))
			result += HIW "��Ŀǰ�����ڳɳ��ڣ����ĸ���ħ������Ϊ��"NOR"\n";
		else
		if (! query("magic/become"))
			result += HIW "��Ŀǰ�Ѵ��ڱ�̬�ڣ����ĸ���ħ������Ϊ��"NOR"\n";
		else
		if (! query("magic/beast"))
			result += HIW "��Ŀǰ�Ѵ��ڳ����ڣ����ĸ���ħ������Ϊ��"NOR"\n";
		else
			result += HIW "��Ŀǰ�����Ϲ����ޣ����ĸ���ħ������Ϊ��"NOR"\n";
		
		if (! query("magic/beast"))
			level = query("magic/level") + "��" + query("magic/lvl") + "��";
		else
		{
			if (query("magic/king1"))
				level = HIY "����̫ʼ";
			else
			if (query("magic/king2"))
				level = HIY "����̫��";
			else
				level = HIM "�Ϲ�����";
		}
	}

	result += "-------------------------------------\n";
	result += HIW "���޵ȼ���" + level + ""NOR"\n";
	result += HIW "����������" + query("magic/armor") + ""NOR"\n";
	result += HIW "ħ�����ԣ�" + chinese_s(query("magic/type")) + ""NOR"\n";
	result += HIW "ħ����ֵ��" + query("magic/power")  + ""NOR"\n";
	result += HIW "�� �� �ȣ�" + query("magic/blood") + ""NOR"\n";
	result += "-------------------------------------\n";

	return result;
}

int heal_up()
{
	object ob;
	string type;
	
	if (present("energy stone", this_object()))
		command("eat energy stone");

	if (! environment() || ! objectp(ob = find_player(query("owner"))))
	{
		save();
		message_vision("$Nһ���Ͳ����ˡ�\n", this_object());
		destruct(this_object());
		return 1;
	}
	
	if (query("mud_age") >= 36000 && ! query("magic/owner"))
	{
		if (! query("magic/level"))
			set("magic/level", 1);
		if (! query("magic/lvl"))
			set("magic/lvl", 1);
					
		if (environment(ob) != environment())
			tell_object(ob, HIW "�����������ԼԼ�ĸ�Ӧ�����ħ����(" + name() + HIW ")Ŀǰ����������"NOR"\n");
		else
		{
			message_sort(HIW "ԭ����ѱ��$N" HIW "ͻ���Դ󷢣��ݺݵ�ҧ��$n�����ֱ�һ�ڣ���"
				"�һ�����һ���Ѫ��������ȥ��Ȼ������$n�Ļ��У������˹���ĺ������ڹ�"
				"��֮�󣬾������������Ľ��ߣ�һ�����ˣ�ȫ���ֽ⡱����ס$n����������"
				"�����⴦���������ֲ�����䣬Ȼ��Ť���ۺϱ仯���ָ�ԭ�Ρ�"NOR"\n", this_object(), ob);
			
			tell_object(ob, HIY + name() + HIY "���ڴ�ʱ����Ϊ���ˣ���ͬʱ����ɳ��ڡ�"NOR"\n");	
			set("magic/owner", ob->query("id"));		       
			set("magic/armor", 1);
			set("magic/power", 1);
			set("magic/blood", 1);
			set("ridable", 1); // ���ʱ��ſ�����Ϊ����Ĺ���
			set("combat_exp",1000);  //�о���
			
			switch(random(5))
			{
				case 0 : type = "gold"; break;
				case 1 : type = "wood"; break;
				case 2 : type = "water"; break;
				case 3 : type = "fire"; break;
				case 4 : type = "soil"; break;
			}
		
			set("magic/type", type);
			tell_object(ob, HIY + name() + HIY "�����ɲ�ǣ���о���һ��" + types[type] + "��"NOR"\n");
			save();
		}
	} else       
	if (query("mud_age") > 36000 && query("mud_age") <= 396000)
	{
		/*
		if (! query_condition("need_upgrade"))
			apply_condition("need_upgrade", 1);
		*/
			
		if (random(10) == 1)   
		tell_object(ob, HIW "�������������Ӧ�����ħ����(" + name() + HIW 
			")��Ҫ�������������䣨upgrade��������"NOR"\n");  
	} else
	if (query("mud_age") > 396000 && query("mud_age") < 432000)  
	{
		if (! query("magic/growup"))
		{
			set("magic/growup", 1);    
			tell_object(ob, HIY + name() + HIY "�ɹ������̬�ڣ����ʱ�����Ƚϴ�������Ҫ��ı�����"NOR"\n");    
		}      

		/*
		if (! query_condition("need_upgrade"))
			apply_condition("need_upgrade", 1);
		*/
		
		if (random(10) == 1)   
		tell_object(ob, HIW "�������������Ӧ�����ħ����(" + name() + HIW 
			")��Ҫ�������������䣨upgrade��������"NOR"\n");     
	} else
	if (query("mud_age") >= 432000)
	{
		if (! query("magic/become"))
		{
			set("magic/become", 1);			     
			tell_object(ob, HIY + name() + HIY "�ɹ���������ڣ�����ӵ���������Ĺ��ܡ�"NOR"\n");     
		}
	}  
	
	if (environment() && environment()->is_chat_room())
		last_age_set = time(); 
	if (! last_age_set) 
		last_age_set = time();	       
    	
	add("mud_age", time() - last_age_set);
    	last_age_set = time();
    	set("age", (int)query("mud_age") / 43200);
	
	/*
	if (query("food") <= 0 || query("water") <= 0)
	{
		if (environment() &&
		    ! environment()->is_chat_room() &&
		    ! query_condition("need_energy"))
		{
			// born & enter the world
			apply_condition("need_energy", 1);
		}
	}
	*/  
	save();  	
	
	// return ::heal_up() ;
	return 1;
}

void init()
{
	if (this_player()->query("id") == query("owner"))
	{
		add_action("do_modify", "modify");
		add_action("do_teach", "teach");
		add_action("do_shape", "shape");
		add_action("do_upgrade", "upgrade");
	}

}


int do_modify(string arg)
{
	string item, msg;
	object me = this_player();
	if(!arg || sscanf(arg,"%s %s",item,msg) != 2)
	return notify_fail("SYNTAX: modify ���� ����\n");
	if(item == "flee")
	{
		set("env/wimpy", atoi(msg));
		write("�ϣ�\n");
		save();
		return 1;
	}

	if(CHINESE_D->check_control(msg))
		return notify_fail("���������п��Ʒ���\n");
	if(CHINESE_D->check_space(msg))
		return notify_fail("�������費���ո�\n");
	if(CHINESE_D->check_return(msg))
		return notify_fail("�������費���س�����\n");

	msg = replace_string(msg, "$BLK$", BLK);
	msg = replace_string(msg, "$RED$", RED);
	msg = replace_string(msg, "$GRN$", GRN);
	msg = replace_string(msg, "$YEL$", YEL);
	msg = replace_string(msg, "$BLU$", BLU);
	msg = replace_string(msg, "$MAG$", MAG);
	msg = replace_string(msg, "$CYN$", CYN);
	msg = replace_string(msg, "$WHT$", WHT);
	msg = replace_string(msg, "$HIR$", HIR);
	msg = replace_string(msg, "$HIG$", HIG);
	msg = replace_string(msg, "$HIY$", HIY);
	msg = replace_string(msg, "$HIB$", HIB);
	msg = replace_string(msg, "$HIM$", HIM);
	msg = replace_string(msg, "$HIC$", HIC);
	msg = replace_string(msg, "$HIW$", HIW);
	msg = replace_string(msg, "$NOR$", NOR);
	msg = replace_string(msg, "$S$", BLINK);
	switch(item)
	{
	case "desc":
		if(CHINESE_D->check_length(msg) > 100)
		return notify_fail("����̫����\n"); 
		set("long",msg+ NOR"\n");
		write("�ϣ�\n");
		save();
		return 1;
	case "nickname" :
		if(CHINESE_D->check_length(msg) > 20)
		return notify_fail("����̫����\n");
		set("nickname",msg+NOR);
		write("�ϣ�\n");
		save();
		return 1;
	case "title" :
		if(CHINESE_D->check_length(msg) > 20)
		return notify_fail("����̫����\n");
		set("title",msg+NOR);
		write("�ϣ�\n");
		save();
		return 1;
	case "arrive_msg" :
		if(CHINESE_D->check_length(msg) > 60)
		return notify_fail("����̫����\n");
		set("arrive_msg",msg+NOR);
		write("�ϣ�\n");
		save();
		return 1;
	case "leave_msg" :
		if(CHINESE_D->check_length(msg) > 60)
		return notify_fail("����̫����\n");
		set("leave_msg",msg+NOR);
		write("�ϣ�\n");
		save();
		return 1;

	}
	return notify_fail("��Ҫ�޸�ʲô��\n");

}

int do_teach(string arg)
{
	object me;
	int gin_cost,amount;
	int myskill, itskill;
	me = this_player();
	if(!myskill = me->query_skill(arg,1))
		return notify_fail("���������󻹲����أ�\n");
	if(arg != "unarmed" && arg != "literate" && arg != "dodge")
		return notify_fail("��ѧ��������ܵģ�\n");
	itskill = query_skill(arg,1);
	if(myskill <= itskill)
		return notify_fail(name()+"�Գ�Ц��Ŀ�������㡣\n");
	if((int)me->query("potential")-(int)me->query("learned_points") < 1)
		return notify_fail("���Ǳ�ܲ�����\n");
	gin_cost = 100/ (int) query_int();
	if((int)me->query("jing") < gin_cost)
		return notify_fail("����Ȼ̫����û�а취�̣�\n");
	me->receive_damage("jing",gin_cost);
	me->add("potential",-1);
	amount = (int)me->query_int() * (int) query_int();
	message_vision(sprintf("$N�����䷳�ؽ�$n��%s����\n",to_chinese(arg)),me,this_object());
	if(random(100) < query("obedience") )
		command("emote �ܲ���Ը�غ���һ����");
	else 
	{
		improve_skill(arg,amount);
		message_vision(sprintf("$N�ƺ����ѧ����һЩ��%s����\n",to_chinese(arg)),this_object());
	}
	return 1;

}

string status_color(int current, int max)
{
	int percent;

	if( max>0 ) percent = current * 100 / max;
		else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}

int do_shape(string arg)
{	
   mapping my;
	string shape;
	int at_pt, pa_pt, do_pt;
	int at_temp,do_temp;
	my = query_entire_dbase();
   printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
	 printf(HIR"����Ѫ��%s%6d/%6d %s(%3d%%)"NOR,status_color(my["qi"],my["eff_qi"]),my["qi"],my["eff_qi"],
		status_color(my["eff_qi"],my["max_qi"]),my["eff_qi"]*100/my["max_qi"]);
    printf(HIC" ��ʳ�%s%6d/%6d [%3d%%]"NOR"\n",status_color(my["food"],max_food_capacity()),my["food"], max_food_capacity(),my["food"]*100/max_food_capacity());
    printf(HIR"������%s%6d/%6d %s(%3d%%)"NOR,status_color(my["jing"],my["eff_jing"]),my["jing"],
		my["eff_jing"],status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"]);
    printf(HIC" ����ˮ��%s%6d/%6d [%3d%%]"NOR"\n",status_color(my["water"], max_water_capacity()), my["water"], max_water_capacity(),my["water"]*100/max_water_capacity());
      
     //   printf("���ˣ� %s\n", my["owner"]);
     //   printf("���飺 %d\t\tɱ���� %d\n",my["combat_exp"],my["bellicosity"]);
     //   printf("�ǻۣ� %d\t\t���ʣ� %d\n",query_int(), query_con());
     //   printf("��̬�� %d\t\t������ %d\n", query_per(), query_str() );
    //    printf("�ٶȣ� %d\n",query_dex() );
	at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
	pa_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_DEFENSE);
	do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
	at_temp=at_pt+1;
	do_temp=pa_pt/2+do_pt/2+1;
	 printf(HIM"��������%9s      "NOR,chinese_number(at_temp));
	 printf(HIM"      ��������%7s "NOR"\n",chinese_number(do_temp));
	 printf(RED"�����ˡ�%7s      "NOR,my["owner_name"]);
	 printf(RED"	��ɱ����%6d "NOR"\n",my["bellicosity"]);

      //  printf("������ %d\t\t������ %d\n\n",at_pt+1, pa_pt/2+do_pt/2+1);
 printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
	return 1;
}


int do_upgrade(string arg)
{
	object me;
	int b_en, b_lv, b_level;
    
	me = this_player();
    
	if (! arg || ! id(arg))
		return notify_fail("��Ҫ���������������ʲô��\n");
	
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");
		
	if (! query("magic/owner"))
		return notify_fail("���ħ������ʱ������Ҫ���������\n");
		
	if (environment(me) != environment())
		return notify_fail("���ħ���޲������㴦��һ�����䡣\n");

	if (me->query("neili") < me->query("max_neili") * 9 / 10)
		return notify_fail("�����������������棬����óȻ���ã�\n");

	if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
		return notify_fail("�����ھ������ã�����óȻ���ã�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����������ʵ������óȻ�����ħ���ޡ�\n");

	if (me->query("max_neili") < 8000)
		return notify_fail("�㳢������һ���������޷�˳"
				   "������һ�����죬����ʩչ���������\n");

	if (me->query("max_jingli") < 1000)
		return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");				
		
	if (me->query("experience") < me->query("learned_experience") + 100) 
		return notify_fail("�����ڻ��۵�ʵս��ỹ̫�٣��޷�����������ħ���ޣ�\n");
		
	message_sort(HIR "$N���о�����ָħ���޼���ͬʱ��ת������������"
		"���澭����ԴԴ������������ע��ħ����($n" HIR ")���ڡ�"NOR"\n", 
		me, this_object());

	if (me->query("max_neili") < me->query_neili_limit() - 400)
	{
		if (random(2) == 1)
		{
			// ����δ������
			message_vision(HIR "$N" HIR "��ɫ��Ȼ���˱䡣"NOR"\n",
				       me);
			tell_object(me, HIC "���Ȼ���õ�����Ϣ��Щ���ҡ�"NOR"\n");
		} else
		{
			message_vision(HIR "$N" HIR "��Ȼ�ƺ�һ������"
				       "��ɲʱ�����죡"NOR"\n", me);
			tell_object(me, HIC "��е����������������δ����"
				    "���������������������ڹ�������"NOR"\n");
			tell_object(me, HIC "��Ļ����ڹ��½��ˡ�\n");
			me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
			return 1;
		}
	}
		
	me->start_busy(1);
	
	me->add("max_neili", -100);
	me->set("neili", (int)me->query("max_neili"));
	me->add("max_jingli", -100);
	me->set("jingli", (int)me->query("max_jingli"));	
	me->add("learned_experience", 100);
	
	tell_object(me, HIW "������Ƭ�̣�����" + name() +
			HIW "�ƺ��������ԣ���Ծ���ݣ�����΢΢һЦ��"NOR"\n");
			
	// apply_condition("need_upgrade", 0);
	
	if (query("magic/owner") && ! query("magic/growup"))
	{
		add("magic/power", 5);
		add("magic/blood", 1);
		add("magic/armor", 2);
		message_vision(RED "$N��ħ����($n" RED ")ħ�������ˣ�"NOR"\n", me, this_object());
		save();
		return 1;
	} else  
	if (query("magic/growup") && ! query("magic/become"))
	{
		add("magic/blood", 1);
		add("magic/armor", 5);
		add("magic/power", 2);  
		message_vision(RED "$N��ħ����($n" RED ")ħ�������ˣ�"NOR"\n", me, this_object());
		save();
		return 1; 
	} else			
	if (query("magic/become"))
	{
		b_en = (int)query("magic/energy");
		b_en++;
	
		set("magic/energy", b_en);
		add("magic/blood", 1);
		
		b_lv = (int)query("magic/lvl");
		
		// if ( b_en >= ((b_lv + 1) * (b_lv + 1) + 10)) 
		if (b_en >= (b_lv * 2))
		{
			b_lv++;
			set("magic/lvl", b_lv);
		
			message_vision(HIY "ħ���������һ����һ���������$N�����壬�����ˣ�"NOR"\n", me);
			message_vision(HIG "$N��ħ���޵������ˣ�"NOR"\n", me);
			
			add("magic/power", 10);
			add("magic/armor", 10);
			set("magic/energy", 0);
		
			b_lv = (int)query("magic/lvl");
			b_level = (int)query("magic/level");       
			if (b_level <= 9 && b_lv % 9 == 0)
			{
				add("magic/power", 200);
				add("magic/armor", 200);
				add("magic/level", 1);
				set("magic/lvl", 1);
				message_vision(HIY "ħ��������ķ����⣬�������Ϲ�����$N�����壬�����ˣ�"NOR"\n", me);
				message_vision(HIG "$N��ħ���޵������ˣ�"NOR"\n", me);
			}		       
			
			if (b_level > 9 && ! query("magic/beast"))
			{
				set("magic/beast", 1); 
				add("magic/power", 800);
				add("magic/armor", 800);       
				message_vision(HIY "ͻȻ��ճ���һ��������ħ��������ĺ����ӣ�ħ����ȫ��ͨ�죡"NOR"\n", me);  
				CHANNEL_D->do_channel(this_object(), "rumor",
					"��˵�Ϲ�����" + name() + HIM + "�������˼䡣");
			}
			     
			save();
			return 1;
		}       
		message_vision(RED "$N��ħ����($n" RED ")ħ�������ˣ�"NOR"\n", me, this_object());
		save();
		return 1;
	}
}

// �ٻ��ӿ�
int receive_whistle(object me)
{
	object env;
	int    period; 

	if ((env = environment()) && env == me)
	{
		if (me->query_temp("is_changing") &&
		    me->query_temp("is_changing") == this_object())
			write(name() + "�Ѿ���������������ˣ����ٻ���ʲô����\n");
		else
			write(name() + "�㲻�������������ٻ���ʲô����\n");
		return 1;
	}
	if (env == environment(me))
	{
		if (is_fighting())
			remove_all_enemy(1);  
		  //set_skill("dodge",query_skill("dodge",1)*2);   
		  //set_skill("unarmed",query_skill("unarmed",1)*2);  
		 // set_skill("literate",query_skill("literate",1)*2);   
					     
		message_vision(name() + "һ���Ͳ����ˡ�\n", me);
		period = time() - ((int) query("last_save"));
		if (period < 0 || period > 900)
		{
			set("last_save", time());
			save(); 
		}
		  me->delete_temp("pet_id");
		destruct(this_object());
		return 1;
	} else
	{
		if (env)
		{
			if (env->is_character() && environment(env))
				env = environment(env);

			message("vision", HIG "ͻȻ" + name() + HIG "����һ����â��"
				HIG "˲����ʧ�ˣ�"NOR"\n", env);

			if (interactive(env = environment()))
			{
				env->delete_temp("is_riding"); 
				delete_temp("is_rided_by");
				tell_object(env, HIM + name() +
					HIM "��Ȼ�����ȥ�ˣ�"NOR"\n");
			}
		}  
		set_skill("dodge",query_skill("dodge",1)*2);  
		message_vision(HIG "$n" HIG "��֪������ܵ�$N" HIG "��ǰ��"NOR"\n",
			me, this_object());
	}
	set_temp("apply/armor", query("magic/armor"));
	
	move(environment(me));

	if (environment() != environment(me))
		return 0;

	return 1;
}

// �����ӿ�
int receive_change(object me)
{
	object ob;
	object env;
	
	ob = this_object();

	if (! query("magic/owner"))
		return 0;
		
	if ((env = environment()) && env == me)
	{
		if (me->query_temp("is_changing") &&
		    me->query_temp("is_changing") == ob)
			write(name() + "�Ѿ���������������ˣ��㻹������ʲô����\n");
		else
			write(name() + "�㲻���������������Ļ�����Ҫ��������������\n");
		return 1;
	}
				
	set_weight(1); 
	move(me);
	set("no_put", "ħ�����Ѿ����������޷��ֿ���");
	set("no_give", "ħ�����Ѿ����������޷��ֿ���");
	set("no_drop", "ħ�����Ѿ����������޷��ֿ���");
	set("no_steal", "ħ�����Ѿ����������޷��ֿ���");
	set("no_get", "ħ�����Ѿ����������޷��ֿ���");	
	set_temp("is_changed_by", me); 
	me->set_temp("is_changing", ob);
	
	if (! query("magic/become"))
	{
		message_sort(HIM "$n" HIM "һ����Х�����ϵ�����ͻ��ʢ������������"
			     "���Ľ��ߣ�һ�����ˣ�ȫ���ֽ⡱����ס$N" HIM "��������"
			     "�������⴦��"NOR"\n", me, ob);
		return 1;
	} 
	me->set_temp("armor/beast", ob);
	me->add_temp("apply/armor", query("magic/armor"));
	message_sort(HIM "$n" HIM "һ����Х�����ϵ�����ͻ��ʢ������������������Ľ�"
		     "ɫ���ƣ�˲�䣬$n" HIM "����������̬����ʼ������$N" HIM "�����ϣ�$n"
		     HIM "��ϸ����֯���ϵ���$N" HIM "���ϸ���λ��ͣ�ĔJ���������ģ�ÿ"
		     "һ�����ֶ���ʼ�𽥵ĳ��Σ���״����һ��飬�����������һ��$N"
		     HIM "�����˼�����ȫ����$n" HIM "��̬��������С�"NOR"\n", me, ob);
	tell_object(me, sort_msg(HIC "�㿴���Լ����������������һ����ȫ����һ����ҫ���ĺ�"
			"ʵ�����У�����������ǽ����Ŀ��ף�������ȴ���Ըо���Ƥ��Ħ"
			"�ĵĸо����ͺ�����һ�����ԭ�����������һ���ݣ��������Ƥ��"
			"һ�������������Ըе�����������΢�磬�Լ�����ɹ�������ϵ����ȡ�\n" 
			NOR), me, ob);       
	return 1;
}	
	
// �������
int receive_recover(object me)
{
	object env;

	if (! (env = environment()) || env != me)
		return 0; 
       
	message_sort(HIM "$N���ϵ�ħ����ϸ��������䣬�����Ϸ�����������һ"
		     "�����$NԼһ�������ң����ڵ��ϣ�Ȼ���ڵ��Ͽ�ʼŤ����"
		     "�ϱ仯�������ģ�����һ�����ޱ���Ϥ�����壭" + name() + 
		     HIM "��"NOR"\n", me);
       
	tell_object(me, sort_msg(HIC "��о����Լ������屻������һ���Ƶģ����ָо�"
		"�޷����ݣ���ʹ����������ȥ��һ��Ƥ�ĸо�ȴ����˵�������"
		"��̡�"NOR"\n"));
		
	move(environment(me));
	delete("no_put");
	delete("no_give");
	delete("no_drop");
	delete("no_steal");
	delete("no_get");	       
	delete_temp("is_changed_by"); 
	me->delete_temp("is_changing");   
	
	if (me->query_temp("armor/beast")&&
	    me->query_temp("armor/beast") == this_object())
	{
		me->delete_temp("armor/beast"); 
		me->add_temp("apply/armor", - query("magic/armor"));
	}
	
	if (environment() != environment(me))
		return 0;
		
	return 1;      
}

int accept_object(object me, object ob)
{
	if (me->query("id") == query("owner")) 
	{
		if (ob->query("id") == "energy stone")
		{
			command("eat energy stone");			
			return 1;
		}
	}
	return 0;
}

void die()
{	
	int i;
	object owner, *enemy;
	int jing, qi, exp;

	
	owner = UPDATE_D->global_find_player(query("owner")); 
	
	if (! objectp(owner)) 
		return ::die();
	
	if (query_temp("is_changed_by")) 
	{
		delete("no_put");
		delete("no_give");
		delete("no_drop");
		delete("no_steal");
		delete("no_get");	       
		delete_temp("is_changed_by"); 
		
		if (owner->query_temp("is_changing") &&
		    owner->query_temp("is_changing") == this_object()) 
			owner->delete_temp("is_changing");
		
		if (owner->query_temp("armor/beast") &&
		    owner->query_temp("armor/beast") == this_object())
		{
			owner->delete_temp("armor/beast"); 
			owner->add_temp("apply/armor", - query("magic/armor"));
		}
	}  
	// owner->set("beastdied", 1);
	
	UPDATE_D->global_destruct_player(owner, 1); 

	exp = (int) query("combat_exp");
	jing = (int) query("max_jing");
	qi = (int) query("max_qi");
	if (! environment()->query("no_death_penalty"))
		set("combat_exp", exp/10 * 9);
	set("eff_qi", qi);
	set("eff_jing", jing);
	set("qi", qi);
	set("jing", jing);

	save();	
	return ::die();
}

void unconcious()
{
	die();
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result; 

	if (! query("magic/owner") || 
	    (query("magic/growup") && 
	    ! query("magic/become")))
		return 0;
	
			
	result = ([ "damage": -query("magic/armor") ]);  

	result += (["msg" :   HIC "$N" HIC "�Ĺ�������$n" 
			      HIC "��ʵ�Ļ����ϡ�"NOR"\n" ]); 

	return result; 
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	if (! query("magic/owner") || 
	    (query("magic/growup") && 
	    ! query("magic/become")))
		return 0;
		
	ob->receive_wound("qi", 200 + query("magic/power"), me);
	       
	return sort_msg(HIR "$N" HIR "���쳯��$n��" HIR "�����΢"
	       "΢������â��һ��Լʮ���ִ�С�Ļ�����$N"
	       HIR "����������ɿ�Ļ���$n" HIR "���ؿڣ�"
	       "$n" HIR "�ŵŵŵĵ����˼���������������"NOR"\n");
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{

	
	if (! mapp(data))
		return 0;
	 
	 

      
	
	if(intp(data["dodge"]) && data["dodge"]!=0) 
	 set_skill("dodge",data["dodge"]);
	
	 if(intp(data["unarmed"])  && data["unarmed"]!=0)
	 set_skill("unarmed",data["unarmed"]);

	if(intp(data["literate"])  && data["literate"]!=0)
	 set_skill("literate",data["literate"]);

	if (mapp(data["magic"]))
		set("magic", data["magic"]);
	
	if (intp(data["ridable"]))
		set("ridable", data["ridable"]);
	
	if (intp(data["age"]))
		set("age", data["age"]);    

	if (intp(data["mud_age"]))
		set("mud_age", data["mud_age"]);	

	if (stringp(data["owner"]))
		set("owner", data["owner"]);
	return 1;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
	mapping data;
	object  user;
	 data=([]);

	

	if (intp(data["dodge"]))
	 data += ([ "dodge" : query_skill("dodge")]);
	
	 if (intp(data["unarmed"]))
	 data += ([ "unarmed" : query_skill("unarmed")]);
	 
	   if (intp(data["literate"]))
	 data += ([ "literate" : query_skill("literate")]);

	if (mapp(query("magic")))
		data += ([ "magic" : query("magic") ]);
       
	if (intp(data["ridable"]))
		data += ([ "ridable" : query("ridable") ]);
		
	if (intp(data["age"]))
		data += ([ "age" : query("age") ]);

	if (intp(data["mud_age"]))
		data += ([ "mud_age" : query("mud_age") ]);		

	if (stringp(data["owner"]))
		data += ([ "owner" : query("owner") ]);  
		
	return data;
}
