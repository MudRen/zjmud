// importer.c
// �û�����������

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define SAVE_DIR	"/data.3k/"
#define SUFFIX_NAME     "fr"
#define SUFFIX_SIZE     26

// ��־�ȼ���Ϊ 3 ������ν綨һ����ϢӦ�ü�¼��
// ��һ������־�У�

// LV 1: �޷������ļ��������û��ȴ�����Ϣ
// LV 2: ���û������ɾ��һ��Ĳ�����Ϣ
// LV 3: ���ƻ����޸����������������Ϣ

#define LOG_LEVEL       3
#define LOG(lv, msg)    log_file(sprintf("transfer/LV%d", lv), msg);

// ��ֵ��� 'nosave' �ؼ��ֲ����ã�
static string suffix = "abcdefghijklmnopqrstuvwxyz";
static string save_dir = SAVE_DIR;

mapping save_dbase;

int     transfer_user(string arg);
void    global_destruct_player(object ob, int raw);
void    transfer_autoload(object user, string card_file);
string *get_user_list(string dir);
object  global_find_player(string user);
mapping assure_user_file(string user, int flag);

void create()
{
	// ����ԭ���� dbased ����
	if (clonep() || ! this_player(1))
	{
		destruct(this_object());
		return;
	}

	seteuid(getuid());
	restore();

	set_name("�û�����������", ({ "data importer", "importer", }));
	set_weight(1);

	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "̨");
		set("long", "����һ̨�û������������������� help "
			    "importer �鿴��ϸʹ��˵����\n");
	}
	setup();

	move(this_player(1));
}

void setup()
{
	::setup();
}

mixed query_object_data(string index) { return save_dbase[index]; }
mapping query_save_dbase() { return save_dbase; }

string query_save_file() { return save_dir + "dbased"; }

void init()
{
	add_action("do_help", "help");
	add_action("do_batch", "batch");
	add_action("do_merge", "merge");
}

int do_help(string arg)
{
	switch (arg)
	{
	case "importer":
		write(@HELP
�����������ʹ��������Щ���û�������������ص����
    batch	���������û����ݡ�
HELP );
		break;

	case "batch":
		write(@HELP_BATCH
ָ���ʽ : batch

���������û����ݡ�

���ָ�import, merge
HELP_BATCH );
		break;

	case "merge":
		write(@HELP_BATCH
ָ���ʽ : merge dbase

������վ������ݿⲢ��Ŀǰվ������ݿ⡣

���ָ�batch
HELP_BATCH );
		break;

	default:
		return notify_fail("��Ҫ�鿴ʲô������\n");
	}

	return 1;
}

// ���һ�����ظ����û���
mapping assure_user_file(string user, int flag)
{
#if 0
	int times;
	mapping file = ([ ]);

	for (times = 0; times < SUFFIX_SIZE; times++)
	{
		file["login_to"] = sprintf("%slogin/%c/%s%c.o", 
					   DATA_DIR, user[0], 
					   user, suffix[times]);

		file["user_to"] = sprintf("%suser/%c/%s%c.o", 
					  DATA_DIR, user[0], 
					  user, suffix[times]);

		file["uid"] = sprintf("%s%c", user, suffix[times]);

		if (file_size(file["login_to"]) < 0 ||
		    file_size(file["user_to"]) < 0)
			return file;
	}
#else
	mapping file = ([ ]);

	file["login_to"] = sprintf("%slogin/%c/%s%s.o", 
				   DATA_DIR, user[0], 
				   user, "_" + SUFFIX_NAME);

	file["user_to"] = sprintf("%suser/%c/%s%s.o", 
				  DATA_DIR, user[0], 
				  user, "_" + SUFFIX_NAME);

	file["uid"] = sprintf("%s%s", user, "_" + SUFFIX_NAME);

	if (flag ||
	    file_size(file["login_to"]) < 0 ||
	    file_size(file["user_to"]) < 0)
		return file;

#endif
	return 0;
}

// ���ָ��Ŀ¼�����е��û��б�
string *get_user_list(string dir)
{
	string *sub_dir_list;
	string  sub_dir;
	string *user_list;
	string *temp_list;

	dir += "login/";

	sub_dir_list = get_dir(dir);
	sub_dir_list = filter_array(sub_dir_list, 
				    (: file_size($(dir) + $1) == -2 :));
	sub_dir_list = map_array(sub_dir_list, (: $(dir) + $1 + "/" :));

	user_list = ({ });

	foreach (sub_dir in sub_dir_list)
	{
		temp_list = get_dir(sub_dir);

		if (! arrayp(temp_list) || ! sizeof(temp_list))
			continue;

		reset_eval_cost();

		temp_list = filter_array(temp_list, (: sscanf($1, "%*s.bak") == 0 :));
		temp_list = map_array(temp_list, (: $1[0..<3] :));
		user_list += temp_list;
	}
	return user_list;
}

// Ѱ�һ����ĳһ����ң���������ʹ�� UPDATE_D �е�ͬ��������
// ����Ϊ����ֱ�������� login_ob���޷��� login_ob  ��������
// ����������Ҫ�õ����������

// �������������Ҫ������Щ�����ߵ���ң������ʹ�øú���
// �������ҵ��벢�ҽ����޸ģ���ע�⣺�޸�����Ժ�������
// ������ң�����ʹ�� global_destruct_player �������������
// ��û�е������������������ҵĶ�ʱ�����Զ�������ҡ�
object global_find_player(string user)
{
	object ob;
	object login_ob;

	ob = find_player(user);
	if (! ob)
	{
		login_ob = new(LOGIN_OB);
		login_ob->set("id", user);
		ob = LOGIN_D->make_body(login_ob);
		if (! ob)
		{
			catch(destruct(login_ob));
			return 0;
		}

		evaluate(bind((: seteuid(getuid()) :), ob));

		if (! ob->restore())
		{
			catch(destruct(login_ob));
			catch(destruct(ob));
			return 0;
		}

		ob->set_temp("temp_loaded", 1);
		ob->set_temp("link_ob", login_ob);

		ob->start_call_out(bind((: call_other, __FILE__, 
				   "global_destruct_player", ob, 0 :),
				   ob), 0);

		login_ob->restore();
		login_ob->set_temp("body_ob", ob);
	}

	return ob;
}

// ����һ���� UPDATE_D ��������
void global_destruct_player(object ob, int raw)
{
	object login_ob;

	if (objectp(ob) && ob->query_temp("temp_loaded"))
	{
		// ���Ӷ� login_ob ������
		if (objectp(login_ob = ob->query_temp("link_ob")))
		{
			if (raw) login_ob->save();
			destruct(login_ob);
		}
		
		if (raw) ob->save();
		destruct(ob);
	}
}

// ����Щ���������Լ������� autoload ���룿

// ����������Ʒ�����ǵ���ҵ� ID ���ܸı��ˣ�
// ������������Ʊ�Ӱ����������ң����Ա���ɾ
// �� autoload�� ���ڿ������ƺ�ֻ����һ�֣���
// �ǵ���һ�ֲ�����Ҫ���ļ�����Ϳ��Բ������
// ��������Լ򵥵�ͨ�� sscanf & filter_array
// �������û��� autoload �б� ���˵� /data/
// Ŀ¼�µ��ļ���
void transfer_autoload(object user, string card_file)
{
	string *autoload;

	autoload = user->query_autoload_info();

	if (! arrayp(autoload) || ! sizeof(autoload))
		return;

	autoload = filter_array(autoload, 
				(: (! sscanf($1, "/data/%*s")) :));
				
	if (stringp(card_file))
		autoload += ({ card_file });

	user->set_autoload_info(autoload);
}

int do_merge(string arg)
{
	mapping m1, m2;
	string  mk;
	string  key, new_key, id, iname;
	object  ob;
	int     ok;

	if (arg != "dbase")
		return notify_fail("��Ҫ����ʲô��\n");

	foreach (key in keys(save_dbase))
	{
		reset_eval_cost();

		if (sscanf(key, DATA_DIR "item/ring/%s", id))
		{
			// Ring information
			new_key = key + "_" + SUFFIX_NAME;
		} else
		if (sscanf(key, DATA_DIR "item/%*s/%s-%s", id, iname) == 3)
		{
			// Item information
			new_key = sprintf(DATA_DIR "item/%c/%s-%s",
					  id[0], id + "_" + SUFFIX_NAME, iname);
		} else
		{
			write("Ignore key - " + key + "!\n");
			continue;
		}

		if (mapp(save_dbase[key]) && mapp(m1 = save_dbase[key]["owner"]))
		{
		    /* Convert data */
		    m2 = allocate_mapping(sizeof(m1));
		    foreach (mk in keys(m1))
		    {
			m2[mk + "_" + SUFFIX_NAME] = m1[mk];
		    }
		    save_dbase[key]["owner"] = m2;
		}

		ok = DBASE_D->set_object_data(new_key, save_dbase[key]);
		if (! ok)
		{
			write(HIR "Failed to set object information: " + new_key + ""NOR"\n");
			continue;
		}

		if (objectp(ob = find_object(new_key)))
			ob->restore();
	}

	return 1;	
}

int do_batch()
{
	int i;
	string *user_list;
	string user;

	user_list = get_user_list(save_dir);

	write(WHT "��ʼǨ���û�����..."NOR"\n");
	
	i = 0;
	foreach (user in user_list)
	{
		/* ��ʼת������־
		for (i = 1; i < LOG_LEVEL + 1; i++)
			LOG(i, "Start transfering (" + user + ")'s data...\n");
		 */

		reset_eval_cost();

		if (transfer_user(user))
		{
			i++;
			write(sprintf("%-15s: Succeed\n", user));
		}
		else write(sprintf("%-15s: " WHT "Failed" NOR "\n", user));
	}
	
	write(WHT "\nǨ���û�������ɣ��� " + sizeof(user_list) + 
	      " ���û����ɹ�Ǩ�� " + i + " ���û���"NOR"\n");
	return 1;
}

// ������������Ϊ�˼򻯴���
#define user_file(x)    sprintf("%suser/%c/%s.o", save_dir, x[0], x)
#define login_file(x)   sprintf("%slogin/%c/%s.o", save_dir, x[0], x)

// ת��ָ�����û�
int transfer_user(string arg)
{
	object  user;
	object  link;
	object  card_ob;

	string  login_from;
	string  user_from;
	string  uid;
	string  card_file;
	string  couple_id;
	string  ring_file;

	string *item_list;
	string  item_name;
	string  item_file;
	string  file_content;

	mapping couple_file;
	mapping file;

	mixed   item_data;

	int     is_ok;

	// �ҵ��ɵ��û��ļ�

	login_from = login_file(arg);
	user_from = user_file(arg);

	if (file_size(login_from) <= 0 || file_size(user_from) <= 0)
	{
		LOG(1, "File not found: (" + login_from + " & " + 
			user_from + ").\n");
		return 0;
	}

	// �����û��ļ��� DATA_DIR

	file = assure_user_file(arg, 0);
	if (! file)
	{
		LOG(1, "User conflict: (" + login_from + " & " + 
			user_from + ").\n");
		return 0;
	}

	if (! cp(login_from, file["login_to"]) || ! cp(user_from, file["user_to"]))
	{
		LOG(1, "Copy file to: (" + file["login_to"] + " | " + 
		       file["user_to"] + ") failed.\n");
		return 0;
	}

	uid = file["uid"];

	if (! objectp(user = global_find_player(uid)))
	{
		LOG(1, "Load user: (" + uid + ") failed.\n");
		return 0;
	}

	if (uid != arg)
	{
		// �޸� LOGIN_OB �� USER_OB �� ID
		if (objectp(link = user->query_temp("link_ob")))
			link->set("id", uid);
	
		user->set("id", uid);
		LOG(2, "User ID (" + arg + ") changed into: (" + 
			uid + ").\n");
	}

	// ���������Ӧ��������������ͬ�����˰ɡ�
	NAME_D->map_name(user->name(), uid);

	// ת������Ϊ������

	// ע����������Կ��Ҫ���ߣ����ǿ��ǵ����е�
	// autoload ��Ʒ�� ����һЩ��������ⶼҪ�����
	// ���������ݲ����ǡ�

	switch (user->query("private_room/type"))
	{
	case "������" : card_file = "/d/room/obj/ultracard"; break;
	case "�ʺ��" : card_file = "/d/room/obj/super"; break;
	case "���־�" : card_file = "/d/room/obj/card"; break;
	default : card_file = 0;
	}

	if (stringp(card_file))
	{
		user->delete("private_room");

		LOG(2, "Deleted (" + arg + ")'s private room.\n");
		LOG(3, "User (" + arg + ") get a free card.\n");
	}

	// ɾ�����塢ͬ�˹�ϵ
	if (user->query("brothers"))
	{
		user->delete("brothers");
		LOG(2, "Deleted (" + arg + ")'s brother relation.\n");
	}

	if (user->query("league"))
	{
		user->delete("league");
		LOG(2, "Deleted (" + arg + ")'s league relation.\n");
	}

	// ɾ������
	user->delete("party");

	// ...on 08/01 21:35.

	// ȷ�ϻ�����ϵ�����ǵ���ż�� ID �п��ܱ仯��
	// ��������Ҫȡ��һ����żΨһ���ܵ� ID�� ȷ
	// �����û��Ļ�����ϵ���������⣬���������ڣ�
	// ������Ѱ�������żΨһ���ܵ� ID ʱ������
	// ż���ļ��Ѿ�ת�Ƶ��� /data/ ���أ��ͻ�Ū
	// ��Ϳ�ˣ���ˣ������Ѿ�ת�ƹ��ģ�Ҫ�޸�Դ
	// Ŀ¼�ڵ��ļ�����
	couple_id = user->query("couple/id");
	
	if (stringp(couple_id))
	{
		// �ı���ż����
		couple_file = assure_user_file(couple_id, 1);
		couple_id = couple_file["uid"];

		user->set("couple/id", couple_id);

		LOG(3, "User (" + arg + ")'s couple/id set to " + 
		       couple_id + ".\n");
		
		// �ţ�Ҫ�Լ����ܺ��Լ��Ľ���ָ
		if (user->query("can_summon/wedding ring"))
		{
			ring_file = sprintf("%sitem/ring/%s.c", DATA_DIR, uid);

			cp(sprintf("%sitem/ring/%s.c", save_dir, arg),
			   ring_file);

			user->set("can_summon/wedding ring", 
				  sprintf("%sitem/ring/%s.c", DATA_DIR, uid));

			LOG(3, "User (" + arg + ")'s wedding ring copied to " + 
			       ring_file + ".\n");
		}

		// ��ԭ���������л�ý�ָ�Ĵ�����
		// Ϣ�����뵽 DBASE_D �С�
		ring_file = sprintf("%sitem/ring/%s", DATA_DIR, arg);
		item_data = query_object_data(ring_file);

		if (item_data)
		{
			item_data["user"] = sprintf("%s(%s)", user->name(), uid);
			is_ok = DBASE_D->set_object_data(sprintf("%sitem/ring/%s", 
							 DATA_DIR, uid), item_data);

			LOG((is_ok ? 3 : 1), "Wedding ring data of (" + arg + 
					     ") port to DBASE_D " + 
					     (is_ok ? "succeed" : "failed") + ".\n");
		}
	}

	// ����������Ʒ

	// ���ԭ����������Ʒ�б�
	item_list = get_dir(sprintf("%sitem/%c/%s-*.c", save_dir, arg[0], arg));

	if (arrayp(item_list) && sizeof(item_list))
	{
		foreach (item_name in item_list)
		{
			// Ҫȥ������� .c ����
			item_file = sprintf("%sitem/%c/%s", DATA_DIR, arg[0], item_name[0..<3]);
			item_data = query_object_data(item_file);

			// �����Ʒ�ľ�������
			sscanf(item_name, arg + "-%s.c", item_name);
			// �����µ���Ʒ�ļ���
			item_file = sprintf("%sitem/%c/%s-%s.c", DATA_DIR, uid[0], uid,
					    item_name);
			// �����ļ�
			is_ok = cp(sprintf("%sitem/%c/%s-%s.c", save_dir, arg[0], arg, item_name), 
				   item_file);

			if (! is_ok)
			{
				LOG(1, "Failed copy Item " + item_name + " of (" + arg + 
				       ").\n");
			} else
			{
				// ���ļ���ȫ����ԭ�����û� ID
				// ����ȫ���滻Ϊ�µ�
				if (arg != uid)
				{
					file_content = read_file(item_file);
					file_content = replace_string(file_content, arg, uid);
	
					write_file(item_file, file_content, 1);
				}
	
				if (item_data)
				{
					// �޸� "user" ��������Ӧ�µ� ID
					item_data["user"] = sprintf("%s(%s)", user->name(), uid);
	
					// ��ԭ������Ʒ������Ϣ���� DBASE_D
					is_ok = DBASE_D->set_object_data(item_file, item_data);
				}
	
				// �����û����ϵ���Ʒ�б�
				user->set("can_summon/" + item_name, item_file);

				LOG(3, "Item " + item_name + " of (" + arg + ") successfully "
				       "tranfered.\n");
			}
		}
	}
	// ת���û��� autoload ��Ϣ��ȥ���޷�����
	// ʹ�õģ��������˿�Ƭ�������ӿ�Ƭ����
	// ����Ϣ
	transfer_autoload(user, card_file);

	// raw : 1���� user ��һ����
	global_destruct_player(user, 1);

	// �޸��ļ�������ʾ���û��Ѿ�ת��
	rename(login_file(arg), login_file(arg) + ".bak");
	rename(user_file(arg), user_file(arg) + ".bak");

	LOG(3, "User (" + arg + ") successfully tranfered.\n");
	return 1;
}
