// versiond.c

#include <ansi.h>
#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>
#include <version.h>
#include <mudlib.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;
inherit F_SAVE;

// �汾ͬ������������ڵķ�������IP��ַ
#define AGENT_IP	({ "127.0.0.1", "202.104.234.74" })

// ɾ������
#define RM_CMD	  "/cmds/wiz/rm"

// ����汾�ļ���Ŀ¼�����Ŀ¼������Ҫ����ͨ�ļ�·��������
// ����ʹ�ã����Բ�����"/"��β����һ���globals.h�е����·
// ������һ������������Ҳ�����������
#define VERSION_DIR     "/version"

// ����汾�ļ����ݵı���(��DBASE�����е�·��)
#define FILES	   "/files"
#define STATS	   "/stats"

// �ڷ������ˣ����ݿ���Ϣ��Ӧ��ֻ��FILES�� ��¼�������ٰ汾
// �е��ļ����޸�ʱ�䣬�Թ��ͻ��������Ƚ��Ƿ��в��
// �ڿͻ��ˣ����ݿ���Ϣ����FILES��STATS�� ����FILES�����˱�
// ��ʹ�õ������ļ��İ汾(���ڷ��������ļ�������޸�ʱ��)��
// ����ͷ������˵�FILES��������ͬ�ġ�����STATS�������һ��
// ͬ���汾��ʱ�����ɵ��ļ���ʱ�䡣����������һ��ͬ���汾
// ��ʱ�����FILES�ڵ�������ͬ���Ϳ�STATS�ͱ����ļ���ʱ��
// �Ƿ��Ǻϣ�������Ǻϣ�˵����Ȼ������û���޸�����ļ�����
// �Ǳ�������ļ�ȴ�Ѿ��������仯��������Ȼ��Ҫͬ����
// ע�⣺STATS��FILES�ǲ�ͬ���ģ��������е�Դ�ļ�".c"��˵��
// ��FILES�м�¼����".c"��·��������STATS��¼����".b"��·����
// ������ΪFILES��Է������ļ�����STATS��Ա����ļ���

// VERSIOND��BUG
// �ڱ������ɰ汾��ʱ��get_file_version���������һ��ģ��
// �ⲿ������binary_valid�������ĳһ��Դ�ļ��Ķ����ƴ�����
// ����ڣ�����һ��DOING��ǿ�ĺ�������Ҫ�޸�MUDOS���ܹ�ʹ�ã�
// ����㲻���޸�MUDOS��������simul_efun ��������д��������
// ���������Ľ���Ч�ʶ�������ʵ�޷�ʹ�ã���˿��Բ��ñ�ͨ��
// ��ʽ�����򵥵ıȽ�Դ�ļ��Ͷ������ļ���ʱ�䣬�����������
// �̳ж����Ƕ���ļ������������ɰ汾��ʱ�����Ҫ����С�ġ�
// ʹ������ǿ��EFUN�����Ժ�Ҳ�����ܱ�֤��ȫ��ȷ��������Ϊ
// �ú���ֻ����˵�һ��̳й�ϵ���������һ��̳е��ļ���ʱ
// �ˣ��ú������޷���顣�����ÿ���޸�һ���ļ����±����ʱ
// ����ÿ���ʹ��updatei �����������̳�������Ȼ������Ȼ
// �п��ܳ������⣬���Ǽ��ʽ����൱��С������仯�Ƚϸ��ӣ�
// ����ȫ�����±��롣

// �Ӱ汾������ȡ�ص��ļ���׺
#define APPENDFIX       ".svr"

// �����Ķ˿�(��MUD�������˿�Ϊ��׼)
#define VERSION_PORT    12

// ����Ҫ�����Ŀ¼
static string *exclude_dir = ({ "/adm/etc", "/adm/simul_efun",
				"/data", "/dump", "/temp", "/binaries", VERSION_DIR,
				// ����
//				"/adm", "/clone", "/doc", "/include", "/help", "/adm", "/d", "/cmds", "/feature", "/kungfu", "/inherit",
				"/backup", "/log", "/u", });
// ������Ҫ������ļ�
static string *include_dir = ({ "/data/e2c_dict.o", "/data/emoted.o", "/data/newsd.o",
				//"/data/analecta",
				"/adm/etc/quest", "/adm/etc/preload" });

// ��Ҫ����CԴ�����Ŀ¼
static string *release_src = ({ "/clone/misc/wedding-ring.c",
				"/d/room/%*s" });

// ��������ƴ����·��
static string bin_path;

// �������ӵ���Ϣ
static mapping socket_info;

// �ͻ��˵�������Ϣ
static mixed *client_info = 0;

// �汾ͨѶ��SOCKET
static int vfd;
static int version_ok;

// build_version����汾ʱʹ�õı���
static int total_error;
static int total_count;
static int total_finish;
static mixed *total_build;

// �ֹ�����ļ��б�
string *fetch_file_list = 0;

#if 0
#define DEBUG_LOG(s)       tell_object(find_player("doing"), s)
#else
#define DEBUG_LOG(s)
#endif

#define T_DEBUG(str) CHANNEL_D->do_channel(this_object(), "debug", str)

// �ṩ���ⲿ�ĺ���
int generate_version();
int build_cancel();
int build_path(string path);
int synchronize_version();
int fetch_file(string file);
int clear_syn_info();
int is_version_ok();
int is_boot_synchronizing();
int is_release_server();
int is_need_release_source(string path);
int append_sn(string file);

// �ڲ�ʹ�õĺ���
private void setup();
private void sys_info(string msg);
private void debug_info(string msg);
private int  connect_server();
private void build_init_data();
private void build_finish();
private void build_version(string path, mapping here);
private int  build_pure_file(mixed *path_info);
private int  get_file_version(string path);
private void send_command(int fd, string cmd);
private int  send_client_pending_msg();
private void syn_receive_result(string str);
private int  syn_receive_file(buffer buf);
private void syn_load_file(string file, int ver);
private void syn_load_version(string path, mapping store);
private void syn_finish();
private void syn_reboot_mud();
private void syn_fetch_file_from_server();
private void syn_check_version_file();
private void syn_read_callback(int fd, mixed str);
private void syn_write_callback(int fd);
private void syn_close_callback(int fd);
private void in_listen_callback(int fd);
private void in_read_callback(int fd, string str);
private void in_write_callback(int fd);
private void in_close_callback(int fd);
private void parse_cmd(int fd);
private void cmd_getver(int fd, string arg);
private void cmd_get(int fd, string arg);
private void send_file(int fd, string file, string peer_name);
private void syn_get_version_data();
private int  send_pending_msg(int fd);
private int  send_result(int fd, string msg);
private int  send_error_msg(int fd, string msg);
private void send_version(int fd);
private void remove_connection(int fd);
private void cmd_close(int fd, string arg);

string query_save_file() { return DATA_DIR + "versiond"; }

int clean_up() { return 0; }

void create()
{
	seteuid(getuid());
	restore();

	// ��ʼ��һЩ��Ϣ
	bin_path = get_config(__SAVE_BINARIES_DIR__);
	set("channel_id", "�汾����");

	// ��û�м��汾
	version_ok = 0;
	total_build = 0;

	// ������ʼ��
	setup();
}

// ��������
void remove(string euid)
{
	if (! this_player())
		return;

	if (sizeof(socket_info) > 0)
		error("�汾���飺Ŀǰ������վ��ͱ�վͬ���汾���㲻�ܴݻٰ汾���顣\n");

	if (! version_ok && vfd)
		error("�汾���飺Ŀǰ�汾����ͬ���У��㲻�ܴݻٰ汾���顣\n");
}

private void setup()
{
	if (RELEASE_SERVER() == "local")
	{
		// ��վ�İ汾�ǲ���Ҫͬ�����µ�
		version_ok = 1;

		// 2s�Ժ��ṩ�汾������
		call_out("in_server", 2);
	} else
	if (stringp(RELEASE_SERVER()) &&
	    sscanf(RELEASE_SERVER(), "%*s %*d") == 2)
	{
		// �����Ƿ�վ�����Ժ���վ����ͬ��
		if (this_player())
		{
			// ����ϵͳ�Զ������ģ���˲����汾
			version_ok = 1;
			write("�����������˰汾���顣\n");
			return;
		}

		// 2s�Ժ����վͬ���汾
		call_out("synchronize_version", 2);
	} else
	{
		// ������Ϣ����ȷ
		write("������Ϣ(/adm/etc/config)����û��ָ���汾������(release server)��\n");
		version_ok = 1;
		return;
	}
}

// �ṩ�汾����
private void in_server()
{
	int port;

	// �����ǰ汾����վ�㣬�ڸö˿��ϼ�����վ������
	// �����汾ͨѶ��SOCKET
	vfd = socket_create(STREAM_BINARY,
			    "in_read_callback",
			    "in_close_callback" );

	if (vfd < 0)
	{
		log_file("version", sprintf("%s Failed to create socket.\n", log_time()));
		return;
	}

	// Ȼ���SOCKET
	port = get_config(__MUD_PORT__) + VERSION_PORT;

	if (socket_bind(vfd, port) < 0)
	{
		log_file("version", sprintf("%s Failed to bind socket.\n", log_time()));
		socket_close(vfd);
		return;
	}

	// ������
	if (socket_listen(vfd, "in_listen_callback" ) < 0)
	{
		log_file("version", sprintf("%s Failed to listen to socket.\n", log_time()));
		return;
	}

	// ��ʼ��������Ϣ
	socket_info = ([ ]);
}

// �ڱ��������ɰ汾
int generate_version()
{
	mapping dbase;
	string file;
	mapping store;

	if (RELEASE_SERVER() != "local")
		return notify_fail("ֻ���ڰ汾������MUD�в����������°汾��\n");

	if (! is_root(previous_object()))
		return 0;

	if (query_heart_beat() || arrayp(total_build))
		return notify_fail("������������汾��\n");

	if (! binary_valid(VERSION_D + ".c"))
		return notify_fail("���ȸ���(update)�汾���飬�Ա�֤�������°汾��\n");

	if (sizeof(socket_info) > 0)
		return notify_fail("Ŀǰ������վ��ͱ�վͬ���汾���㲻�ܹ���汾��\n");

	// ���������core�ļ�����ɾ��֮
	rm("/core");

	// ��ԭ�����еİ汾��Ϣ���ݱ��浽��ʱ������
	set_temp(FILES, query(FILES));
	delete(FILES);

	// ������������
	set("VERSION_NO", time());

	log_file("version", sprintf("%s new version [%d] now generated.\n",
				    log_time(), query("VERSION_NO")));

	// ����/Ŀ¼����İ汾
	store = ([ ]);
	set(FILES, store);

	// ��ʼ��������Ϣ
	build_init_data();
	
	message_system("ϵͳ�������ɿ���ִ�еķ����汾��������Ϸ�ٶȿ��ܻ��ܵ�Ӱ�졣\n");
	write("��ʼ���ɰ汾...\n");

	build_version("/", store);

	// �������ж����ļ��İ汾
	foreach (file in include_dir)
		build_version(file, 0);

	// ��ʼ���������а汾����
	set_heart_beat(1);
	log_file("version", sprintf("%s %s start build version.\n",
				    log_time(), this_player() ? geteuid(this_player()) : "SYSTEM"));

	return 1;
}

// ��ֹ���ɰ汾
int build_cancel()
{
	if (! arrayp(total_build))
		return notify_fail("���ڲ�û���������ɰ汾��\n");

	// ����汾��
	set("VERSION_NO", 0);
	save();

	// �������
	build_finish();

	// ֹͣ����
	set_heart_beat(0);
	write("��ֹ���������ɰ汾�Ĳ�����Ŀǰ�İ汾�������ְ汾֮�䣬���ܻᵼ�²��ȶ���\n");
	return 1;
}

// ��������������汾�����е���ͨ�ļ�
private void heart_beat()
{
	int n;
	int percent;
	mixed *piece;

	if (! arrayp(total_build))
	{
		// ����û�а汾��������
		set_heart_beat(0);
		return;
	}

	n = 0;
	while (n < 100 && sizeof(total_build))
	{
		// ����ĳһ��Ŀ¼
		reset_eval_cost();
		piece = total_build[0];
		total_build = total_build[1..<1];
		n += build_pure_file(piece) + 1;
	}

	total_finish += n;
	if (total_count < total_finish) total_count = total_finish;

	percent = total_finish * 100 / total_count;
	if (percent / 10 != query_temp("last_prompt") / 10)
	{
		// ÿ��10%����ʾһ�������û���
		message_system("ϵͳ����汾�У��Ѿ���� " + percent + "%...");
		set_temp("last_prompt", percent);
	} else
		sys_info("�Ѿ���� " + percent + "%...");

	if (sizeof(total_build))
		return;

	// �������
	save();
	log_file("version", sprintf("%s Total %d error when generate version [%d]\n",
				    log_time(), total_error, query("VERSION_NO")));
	sys_info("�汾������ϡ������ɰ汾��һ�������� " + total_error + " ������");
	message_system("ϵͳ���ɰ汾��ϡ�\n");

	// ��ԭ����
	build_finish();

	set_heart_beat(0);
}

// ����һ���µİ汾��
int build_new()
{
	int ver;

	if (! is_root(previous_object()))
		return notify_fail("ֻ��ROOT_UID����Ȩ�޵������������\n");

	// �ж����ڵ�״̬
	if (arrayp(total_build))
		return notify_fail("������������汾��\n");

	// �����µİ汾��
	set("VERSION_NO", ver = time());
	save();
	write(sprintf("�������µİ汾�ţ�%d\n", ver));
	return 1;
}

// ����ĳ��·������İ汾
int build_path(string path)
{
	if (! is_root(previous_object()))
		return notify_fail("ֻ��ROOT_UID����Ȩ�޵������������\n");

	if (sizeof(socket_info) > 0)
		write("Ŀǰ������վ��ͱ�վͬ���汾����������İ汾��\n");

	// ȥ��ĩβ��"/"
	while (strlen(path) > 1 && path[strlen(path) - 1] == '/')
		path = path[0..<2];

	if (file_size(path) == -1)
		return notify_fail("û�ж�Ӧ���·�������ļ�����·�������ܽ���汾��\n");

	bin_path = get_config(__SAVE_BINARIES_DIR__);
	if (path[0..strlen(bin_path) - 1] == bin_path)
		return notify_fail("�������ļ�����Ҫ����汾��\n");

	// �ж����ڵ�״̬
	if (arrayp(total_build))
		return notify_fail("������������汾��\n");

	if (! binary_valid(VERSION_D + ".c"))
		return notify_fail("���ȸ���(update)�汾���飬�Ա�֤�������°汾��\n");

	// ���������core�ļ�����ɾ��֮
	rm("/core");

	build_init_data();
	write("���ڿ�ʼ����汾��\n");
	build_version(path, 0);

	log_file("version", sprintf("%s %s start build path(%s).\n",
				    log_time(),
				    this_player() ? geteuid(this_player()) : "SYSTEM",
				    path));
	if (sizeof(total_build))
		// �д��ļ���Ҫbuild����������
		set_heart_beat(1);
	else
	{
		save();
		write("������ϡ�\n");
		build_finish();
	}

	return 1;
}

// ��ʼ�����������
private void build_init_data()
{
	total_build = ({ });
	total_error = 0;
	total_count = 0;
	total_finish = 0;
}

// �������������
private void build_finish()
{
	total_build = 0;
	total_error = 0;
	total_count = 0;
	total_finish = 0;

	// ����������ʾ�ı���
	set_temp("last_prompt", 0);

	// ȥ����¼�ļ��汾��ʹ�õ���ʱ����
	delete_temp(FILES);
}

// build_version�������а���Ҫ�������Ϣ���뵽total_build��
// �����ݼ����У�������֯��ʽ���£�
// total_build ----+-- Ŀ¼��Ϣ1 --+-- ȫ·����
//		 |	       |
//		 |	       +-- ���ļ�������
//		 |
//		 +---Ŀ¼��Ϣ2 --+-- ȫ·����
//		 |	       |
//		 |	       +-- ���ļ�������
//		 ...
// total_error ���������

// ���ĳ��·���Ĺ���
// ���ظ�·�����ļ�����Ŀ
private int build_pure_file(mixed *path_info)
{
	int count;
	string path;
	mapping here;
	string pname;
	string file;
	int ver;

	// ȡ�����ȫ·����
	path = path_info[0];

	// ��֤�汾Ŀ¼�½����˺��ʵ�·��(����������·��)
	assure_file(VERSION_DIR + bin_path + path + "???");
	assure_file(VERSION_DIR + path + "???");

	// ȥ������'/'��������dbase��query������
	if (strlen(path) > 1) pname = path[0..<2];

	// �鿴�Ƿ���Ϊ���·��׼���ð汾���ݽṹ�����û��
	// �ʹ������ݽṹ
	if (! mapp(here = query(FILES + pname)))
	{
		here = ([ ]);
		set(FILES + pname, here);
	}

	// ȡ���е��ļ��İ汾
	count = 0;
	foreach (file in path_info[1])
	{
		// ����һ����ͨ�ļ�
		if (! (ver = get_file_version(path + file)))
			total_error++;
		else
			here[file] = ver;
		count++;
	}

	return count;
}

// ����ĳ��·������İ汾
private void build_version(string path, mapping here)
{
	mixed piece;
	mixed *files;
	string *pure_files;
	int ver;

	if (member_array(path, exclude_dir) != -1)
		// ����ļ�����Ҫ����汾��ֱ�ӷ��سɹ�
		return;

	if (! mapp(here))
	{
		// û��ָ��������ɵİ汾��Ϣ��λ�ã������
		// ��·�������ԣ���ͨ�ļ�����Ŀ¼
		switch (file_size(path))
		{
		case -1:
			// û�����Ŀ¼�����ļ���ֱ�Ӽ���
			return;
	
		case -2:
			// ����һ��Ŀ¼����������Ҫȷ�����ɺ��ʵ�ӳ
			// ������
			here = ([ ]);
			set(FILES + path, here);
			break;
	
		default:
			// ����һ����ͨ�ļ���ֱ�����ɰ汾��Ϣ

			// ���ȱ�֤�汾Ŀ¼�½����˺��ʵ�·��(����������·��)
			assure_file(VERSION_DIR + bin_path + path + "???");
			assure_file(VERSION_DIR + path + "???");

			if ((ver = get_file_version(path)) > 0)
				set(FILES + path, ver);
			return;
		}
	}

	// ȡ���·������������ļ�
	if (path[strlen(path) - 1] != '/') path += "/";
	files = get_dir(path, -1);
	if (! arrayp(files))
		// û�����·��
		return 0;

	// ��ʾ
	sys_info("��������·����" + path);

	// ������Ŀ¼����������ļ�
	foreach (piece in files)
	{
		reset_eval_cost();
		switch (piece[1])
		{
		case -2:
			// ����һ��Ŀ¼��������һ��������
			here[piece[0]] = ([ ]);
			build_version(path + piece[0], here[piece[0]]);
			piece[0] = 0;
			break;

		default:
			// ����һ����ͨ�ļ����Թ��������Ժ�����
			break;
		}
	}

	// ����Ŀ¼��Ϣ���Դ������������
	pure_files = map_array(files, (: ((mixed *) $1)[0] :));
	pure_files -= ({ 0 });
	if (sizeof(pure_files))
	{
		total_build += ({ ({ path, pure_files }) });
		total_count += 1 + sizeof(pure_files);
	}
}

// �Ƿ���Ҫ����Դ����
int is_need_release_source(string path)
{
	string *files;
	string match;

	foreach (match in release_src)
		if (path == match || sscanf(path, match) == 1)
			return 1;

	return 0;
}

// �����ļ�������ʱ��(C�򷵻ض����ƴ����ʱ��)��Ϊ�汾
private int get_file_version(string path)
{
	int last;
	mixed *st, *cst;
	string bpath;
	string cpath;
	object ob;
	object *uobs;
	int ver;
	int need_reload;

	cst = stat(path);
	if (! arrayp(cst) || sizeof(cst) < 2 || cst[0] < 0)
	{
		// û���ҵ�����ļ���
		log_file("version", sprintf("%s can't find file: %s\n",
					    log_time(), path));
		return 0;
	}

	last = strlen(path) - 2;
	if (last > 0 && path[last + 1] == 'c' && path[last] == '.' &&
	    ! is_need_release_source(path))
	{
		// ����һ�����ܷ�����c�ļ����ұ���ȡ���Ķ���
		// �ƴ����ļ�
		bpath = bin_path + path[0..last] + "b";
		st = stat(bpath);
		if (! arrayp(st) || sizeof(st) < 2)
			// û������ļ�
			need_reload = 1;
		else
		if (st[0] == -2)
		{
			// ����һ��Ŀ¼
			RM_CMD->rm_dir(bin_path);
			need_reload = 1;
		} else
#if 1
		if (! binary_valid(path))
			// ���ļ���Ҫ���±���
			need_reload = 1;
#else
		// doing �������������жϵ����±����������
		// ֻҪBIN�ļ�������ʱ�䲻����C�ļ���ʱ���
		// ��Ϊ����Ҫ���룬����Ϊ�˱��⹹��汾����
		// ̫���ʱ�䡣ÿ���޸�һЩ�ļ��Ժ���ʹ��
		// updatei �������м̳��ļ���
		if (st[1] < cst[1])
			// ���ļ���Ҫ���±���
			need_reload = 1;
#endif

		if (need_reload)
		{
			// û�����µ�binaries�ļ�������Ҫ��
			// �±�������ļ���
			if (objectp(ob = find_object(path)))
			{
				// �ҵ������OBJECT����¼���������
				uobs = filter_array(all_inventory(ob), (: playerp($1) || $1->is_character() && $1->query_temp("born_time") :));
				uobs->move(VOID_OB, 1);
				destruct(ob);
			}

			// ��������OBJECT
			reset_eval_cost();
			catch(ob = load_object(path));
			if (objectp(ob) && sizeof(uobs))
				// �ƶ������ԭ�ȵ�OBJECT
				uobs->move(ob, 1);

			if (file_size(bpath) < 0)
			{
				// ��û������ļ����п�����
				// �������
				log_file("version", sprintf("%s can't get binaries: %s\n",
							    log_time(), path));
				return 0;
			}

			// ���BIN�϶��Ǹո����ɵģ�ֱ
			// �ӷ��ء�
			ver = time();
		} else
			// ����BIN�ļ�������ʱ����Ϊ�汾��
			ver = st[1];

		// ��¼��Ҫ���Ƶ�Դ�ļ�����(C��Ҫ����BIN�ļ�)
		cpath = bpath;
	} else
	{
		// ����c�ļ���ֱ�ӷ���ʱ����Ϊ�汾��
		ver = cst[1];

		// ��¼��Ҫ���Ƶ�Դ�ļ�����(��ͨ�ļ�ֱ�Ӹ���)
		cpath = path;
	}

	// ��������ļ��İ汾�����һ������ʱ�İ汾��һ�£�
	// ���ǰ汾Ŀ¼��û������ļ����������е��ļ�����
	// ���汾Ŀ¼��ȥ��ע�⣺������һ��ȱ�ݣ��Ǿ������
	// �޸��˰汾Ŀ¼�е��ļ�����ôϵͳ�������飬����
	// ��Ϊ���ļ��汾��Ȼ��ȷ�������޸�VERSION �������
	// ���Ǿ��Ա���ֹ�ġ�
	switch (file_size(VERSION_DIR + cpath))
	{
	case -2:
		// �汾�д�ŵ���һ��·������ô����
		// Ҫ���������·����
		sys_info(sprintf("file(%s) is a path in version dir, removed.", cpath));
		RM_CMD->rm_dir(VERSION_DIR + cpath);
		break;
	case -1:
		break;

	default:
		// ����ļ��Ѿ����ڣ��Ƚϼ�¼�İ汾��Ϣ
		if (ver == query_temp(FILES + path))
			// �汾��ͬ�����ؼ��ɡ�
			return ver;
	}

	// ��Ҫ��������ļ�����汾·��
	cp(cpath, VERSION_DIR + cpath);
	last = strlen(cpath) - 2;

	if (cpath[last] == '.' && (cpath[last + 1] == 'c' || cpath[last + 1] == 'h'))
		// Դ������Ҫ����������ID
		append_sn(VERSION_DIR + cpath);

	return ver;
}

// ��÷������ϵ��ļ�
int fetch_file(string file)
{
	object me;

	if (RELEASE_SERVER() == "local")
		return notify_fail("�ڰ汾����վ��������ӷ������ϻ���ļ���\n");

	if (arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
		return notify_fail("���ڰ汾����ͬ���С�\n");

	if (find_call_out("syn_reboot_mud") != -1)
		return notify_fail("���ڰ汾������������������Ϸ���޷�ͬ����\n");

	fetch_file_list = ({ file });

	if (objectp(me = this_player(1)))
		set_temp("operator", filter_color(me->name(1)) + "(" +
				     geteuid(me) + ")");
	else
		delete_temp("operator");

	if (! connect_server())
		return 0;

	write("�������ӷ�������ȡ�ļ���\n");
	return 1;
}

// ͬ�������汾
int synchronize_version()
{
	object me;

	if (RELEASE_SERVER() == "local")
		return notify_fail("�ڰ汾����վ��������ͬ�����°汾��\n");

	if (arrayp(client_info) && client_info[STATUS] != STATUS_FINISHED)
		return notify_fail("���ڰ汾����ͬ���С�\n");

	if (find_call_out("syn_reboot_mud") != -1)
		return notify_fail("���ڰ汾������������������Ϸ���޷�ͬ����\n");

	// �����������֤ͬ���汾
	fetch_file_list = 0;

	if (objectp(me = this_player(1)))
		set_temp("operator", filter_color(me->name(1)) + "(" +
				     geteuid(me) + ")");
	else
		delete_temp("operator");

	// ���ñ�־���汾��û�гɹ���ͬ��
	version_ok = 0;
	delete_temp("version_changed");

	if (! connect_server())
		return 0;

	write("�㿪ʼ�ͷ�����ͬ���汾��\n");
	return 1;
}

private int connect_server()
{
	string addr, port;
	int ret_val;

	// �����汾ͨѶ��SOCKET
	vfd = socket_create(STREAM_BINARY,
			    "syn_read_callback",
			    "syn_close_callback" );

	if (vfd < 0)
	{
		log_file("version", sprintf("%s Failed to create socket.\n",
					    log_time()));
		return notify_fail("�޷�����SOCKET.\n");
	}

	// ��ʼ���ͻ�����Ϣ
	client_info = allocate(8);
	client_info[STATUS] = STATUS_CONNECTING;
	client_info[FILE_NAME] = 0;
	client_info[FILE_POS] = 0;
	client_info[FILE_SIZE] = 0;
	client_info[RESULT_BUFFER] = "";
	client_info[PENDING_WRITE] = ({ });

	if (sscanf(RELEASE_SERVER(), "%s %d", addr, port) != 2)
	{
		log_file("version", sprintf("%s Bad address(%s) of server.\n",
					    log_time(), RELEASE_SERVER()));
		return notify_fail("���õİ汾�������ĵ�ַ����ȷ��\n");
	}

	// ���ɰ汾�����������ӵ�ַ
	if (! stringp(addr = CONFIG_D->query("server agent")) ||
	    sscanf(addr, "%*s %*d") != 2)
		addr = sprintf("%s %d", addr, port);

	ret_val = socket_connect(vfd, addr,
				 "syn_read_callback",
				 "syn_write_callback");
	if (ret_val != EESUCCESS)
	{
		log_file("version", sprintf("%s Failed to connect server.\n",
					    log_time()));
		return notify_fail("�޷����Ӱ汾��������\n");
	}

	log_file("version", sprintf("%s connecting to server %s.\n",
				    log_time(), addr));
	return 1;
}

// ���ͬ����Ϣ
int clear_syn_info()
{
	int result;
	int fd;

	if (previous_object() && ! is_root(previous_object()))
		return 0;

	// �������ˣ�����׽��ֵ�������Ϣ
	if (is_release_server())
	{
		if (sizeof(socket_info) > 0)
		{
			foreach (fd in keys(socket_info))
				if (intp(fd)) socket_close(fd);

			socket_info = ([ ]);
			return 1;
		}

		return 0;
	}

	// �ͻ��ˣ����ͬ����SOCKET����Ϣ
	if (vfd)
	{
		log_file("version", sprintf("%s ��ͣ��ͬ���汾�Ĳ�����\n", log_time()));
		syn_finish();
		return 1;
	}

	return 0;
}

// �汾�Ƿ�����
int is_version_ok() { return version_ok; }

// �Ƿ����ڽ�������ʱͬ���汾
int is_boot_synchronizing()
{
	if (! version_ok && ! stringp(query_temp("operator")))
		return 1;	   
}

// �Ƿ��ǰ汾����������
int is_release_server() { return RELEASE_SERVER() == "local"; }

// ����
#if 0
mixed query_client_info() { return client_info; }
int query_vfd() { return vfd; }
#endif

// ���������Ϣ
mixed query_socket_info()
{
	if (previous_object() && ! is_root(previous_object()))
		return 0;

	return socket_info;
}

// �ӷ���������ļ�
private void syn_get_file(string file)
{
	if (client_info[STATUS] != STATUS_SYN)
		return;

	send_command(vfd, "get " + file);
}

// �ӷ�������ð汾����
private void syn_get_version_data()
{
	if (client_info[STATUS] != STATUS_GET_VERSION)
		return;

	// ����״̬��Ϊ���ڻ���ļ�
	client_info[STATUS] = STATUS_GET_VERSION_DATA;
	send_command(vfd, "getver dbase");
}

// ��������˷�������
void send_command(int fd, string cmd)
{
	if (! fd)
		// ��鵱ǰ���ӵ�VFD
		if (! (fd = vfd)) return;
		

	cmd += "\n";
	if (sizeof(client_info[PENDING_WRITE]))
	{
		// �Ѿ���������Ҫ���͵������ˣ���η��͵���
		// ��������
		client_info[PENDING_WRITE] += ({ cmd });
		return;
	}

	switch (socket_write(fd, cmd))
	{
	case EESUCCESS:
	case EECALLBACK:
		// ���ͳɹ���
		return;

	case EEWOULDBLOCK:
		// ������������
		client_info[PENDING_WRITE] += ({ cmd });
		call_out("syn_write_callback", 2, fd);
		return;

	default:
		// ����ʧ��
		client_info[PENDING_WRITE] += ({ cmd });
		return;
	}
}

// �ͻ��˷�����������Ϣ
private int send_client_pending_msg()
{
	string msg;

	msg = client_info[PENDING_WRITE][0];
	switch (socket_write(vfd, msg))
	{
	case EESUCCESS:
		// ���ͳɹ���
		client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
		return 0;

	case EECALLBACK:
		// ��Ҫ�ȴ�
		client_info[PENDING_WRITE] = client_info[PENDING_WRITE][1..<1];
		return -1;

	case EEWOULDBLOCK:
		// ������������
		call_out("syn_write_callback", 2, vfd);
		return -1;

	default:
		// ����ʧ��
		return -1;
	}
}

// ͬ��ʱ�ͻ������ӵĶ��ص�����
// ���ڷ��������ܻ᷵���������ݣ�1 ��ͨӦ����Ϣ  2 ��������
// �����ݡ���˽��պ�������״̬�е��ļ����ִ��������������
// ����״̬��������ļ����֣���ô����Ϊ�ǽ����ļ��У����û
// �У����ǽ�����ͨӦ����Ϣ����ͨӦ����Ϣһ���ǹ̶����ֽڣ�
// ��ASCII ��ʽ��š����һ�ν���û�������������ֽڣ���ô��
// �Ƚ�������FILE_POS���档
private void syn_receive_result(string str)
{
	string file;
	string msg;
	int len;
	int ver;
	string op;

	if ((len = strsrch(str, '\n')) == -1)
	{
		// ���ص���Ϣ����ȷ - �������'\n'
		log_file("version", sprintf("%s respond without '\\n' from server: %s.\n",
					    log_time(), str));
		DEBUG_LOG(sprintf(HIR "error syntax str = %s"NOR"\n", str));
		return;
	}
	if (! len) return;
	str = str[0..len - 1];

	DEBUG_LOG(sprintf("str = %s\n", str));
	op = query_temp("operator");

	if (sscanf(str, RESULT_ERR "%s", msg))
	{
		// �����˴����ȼ�¼������־
		log_file("version", sprintf("%s error respond: %s\n",
					    log_time(), msg));
		DEBUG_LOG(str + "\n");
	}

	// ���ݵ�ǰ��״̬���д���
	switch (client_info[STATUS])
	{
	case STATUS_GET_VERSION:
		// ���ڶ�ȡ�汾
		if (sscanf(str, RESULT_VERSION "%d", ver))
		{
			// �����˰汾
			log_file("version", sprintf("%s get version from server: %d\n",
						    log_time(), ver));

			// ��ʼ��ð汾�ļ�
			if (query("VERSION_NO") != ver)
			{
				if (! stringp(op) && CONFIG_D->query("manual_synchronize"))
				{
					// ϵͳ�Ծ٣������������ֹ�ͬ���汾�ı�־
					sys_info("���ذ汾��Ҫ���£�����ϵͳ"
						 "�����Զ�ͬ����\n");
					version_ok = 1;
					set_temp("version_changed", 0);
					syn_finish();
					break;
				}

				// �汾��һ��
				log_file("version", sprintf("%s local version(%O) is not ok.\n",
							    log_time(), query("VERSION_NO")));
				if (stringp(op))
				{
					// ��ʾ��ʾ��Ϣ
					sys_info(sprintf("%sҪ��ͬ���汾�����ص�"
							 "�汾(%O)��Ҫ����Ϊ(%O)��",
							 op, query("VERSION_NO"), ver));
					message_system(sprintf("%s���ڽ���������ͬ���汾��", op));
				}

				set_temp("version_changed", 1);
				syn_get_version_data();
			} else
			{
				// �汾һ��
				log_file("version", sprintf("%s local version ok.\n", log_time()));
				if (stringp(op = query_temp("operator")))
					// ��ʾ��ʾ��Ϣ
					sys_info(sprintf("%sҪ��ͬ���汾�����Ǳ���"
							 "�汾�Ѿ��ͷ���������һ���ˡ�", op));
				version_ok = 1;
				set_temp("version_changed", 0);
				syn_finish();
			}
			break;
		}

		// û�з��������İ汾��Ϣ
		log_file("version", sprintf("%s can not get version. server report: %s\n",
					    log_time(), str));

		// ��ô�죿ֻ�н���ͬ��
		syn_finish();
		break;

	case STATUS_GET_VERSION_DATA:
		// ��ð汾���ݣ�ִ�к�STATUS_GET_SYN��ͬ

	case STATUS_SYN:
		// �����ļ��ĳ���
		if (! sscanf(str, RESULT_FILE "%s %d", file, len))
		{
			if (sscanf(str, RESULT_FINISH "%*s"))
			{
				log_file("version", sprintf("%s version synchronized.\n",
							    log_time()));
				if (stringp(op))
					message_system(sprintf("%s�Ѿ����汾������ϡ�", op));
				// ͬ����ϣ�����汾��Ϣ
				save();
				version_ok = 1;

				// ��ȡnews/chinesed/emoted
				reset_eval_cost();
				catch(NEWS_D->restore());
				catch(CHINESE_D->restore());
				catch(EMOTE_D->restore());
				syn_finish();
			}

			break;
		}

		DEBUG_LOG(sprintf("file: %s len = %d\n", file, len));

		// ��¼�Ľ����ļ�״̬����Ϣ
		if (client_info[STATUS] == STATUS_GET_VERSION_DATA)
			// ���ڶ�ȡ�汾��Ϣ�������ļ�����
			file = query_save_file() + __SAVE_EXTENSION__;

		// ��¼���������ļ�����Ϣ
		client_info[FILE_NAME] = file;
		client_info[FILE_POS] = 0;
		client_info[FILE_SIZE] = len;

		// ����У�ɾ������ļ�����ʱ�ļ�
		rm(file + APPENDFIX);

		sys_info(sprintf("getting(%s)...", file));
		break;

	default:
		// ��Ӧ�ý��յ���Ϣ
	}
}

// �����ļ�����
private int syn_receive_file(buffer buf)
{
	mixed *st;
	string file;
	int len;
	int sl;

	file = client_info[FILE_NAME];
	len =  client_info[FILE_SIZE] - client_info[FILE_POS];
	if (len > sizeof(buf))
		// ����Ҫ��buf�е�����ȫ��д��
		len = sizeof(buf);

	write_buffer(file + APPENDFIX,
		     client_info[FILE_POS], buf[0..len - 1]);
	client_info[FILE_POS] += len;
	if (client_info[FILE_POS] < client_info[FILE_SIZE])
		// �ļ���û�н������
		return len;

	// �ɹ���ȡ�ļ����
	log_file("version", sprintf("%s got file %s.\n",
				    log_time(), client_info[FILE_NAME]));
	client_info[FILE_POS] = 0;
	client_info[FILE_NAME] = 0;
	client_info[FILE_SIZE] = 0;

	// �鿴��ǰ��״̬
	switch (client_info[STATUS])
	{
	case STATUS_GET_VERSION_DATA:
		// ����˰汾���ݣ���ȡ����
		file += APPENDFIX;
		rm(file + __SAVE_EXTENSION__);
		rename(file , file + __SAVE_EXTENSION__);

		// �ھ�̬�����м�¼���ص��ļ��汾���ļ���Ϣ
		set_temp(FILES, query(FILES));
		set_temp(STATS, query(STATS));
		delete(FILES);
		delete(STATS);

		if (! restore_object(file))
		{
			log_file("version", sprintf("%s can not read version-dbase got from server.\n",
						    log_time()));
			rm(file + __SAVE_EXTENSION__);
			syn_finish();
			return sizeof(buf);
		}

		// ɾ�����ļ�
		rm(file + __SAVE_EXTENSION__);

		// ��ʼͬ�����е��ļ�
		syn_check_version_file();
		break;

	case STATUS_SYN:
		// ���ļ������޸�Ϊ����������
		rm(file);
		rename(file + APPENDFIX, file);

		// �������ļ���һ��C�ļ�����ô�ұ���ɾ��
		// ����BIN �ļ�����Ϊ����Ҫ���±�������
		sl = strlen(file) - 2;
		if (sl > 0 && file[sl] == '.' && file[sl + 1] == 'c')
			rm(bin_path + file[0..sl] + "b");

		// �Ҽ�¼����ļ�����Ϣ�������һ��BIN�ļ���
		// ��ô���б�Ҫ��¼C�ļ���ʱ�䣬����ͼ�¼
		// ���ļ�����
		if (sscanf(file, bin_path + "%s", file) &&
		    strlen(file) > 1)
			file[strlen(file) - 1] = 'c';

		st = stat(file);
		if (arrayp(st) && sizeof(st) >= 2)
			set(STATS + file, st[1]);

		break;

	default:
		// �����״̬
	}

	// ����ʹ�õ�BUFFER�ĳ���
	return len;
}

// �ӷ������ϻ�ȡһ���ļ�
private void syn_fetch_file_from_server()
{
	int i;

	client_info[STATUS] = STATUS_SYN;

	for (i = 0; i < sizeof(fetch_file_list); i++)
	{
		sscanf(fetch_file_list[i], VERSION_D "/%s", fetch_file_list[i]);
		if (fetch_file_list[i][0] != '/')
			fetch_file_list[i] = "/" + fetch_file_list[i];
		send_command(vfd, "get " + fetch_file_list[i]);
	}

	send_command(vfd, "close");
}

// �Ƚϰ汾�����е��ļ�
private void syn_check_version_file()
{
	mapping store;
	string file;

	// �л�״̬Ϊͬ��״̬
	client_info[STATUS] = STATUS_SYN;

	if (! mapp(store = query(FILES)))
	{
		// û�а汾��Ϣ
		log_file("version", sprintf("%s can not synchronize version "
					    "without version's dbase.\n",
					    log_time()));
		syn_finish();
		return;
	}

	// ȷ��û�б��ص��ļ���Ϣ
	delete(STATS);

	// ������е��ļ�
	syn_load_version("/", store);

	// �������ж����ļ��İ汾
	foreach (file in include_dir)
		syn_load_version(file, _query(store, explode(file, "/")));

	// ����汾
	send_command(vfd, "close");
	log_file("version", sprintf("%s total %d commands generated.\n",
				    log_time(), sizeof(client_info[PENDING_WRITE])));
}

// ��鲢���ĳһ���ļ�
// ����������ͱ��ض�û���޸�ĳ���ļ�������Ҫͬ���������
// һ���޸��ˣ�����Ҫͬ����
// ����������޸��ˣ���ô����Ĳ���ver�ͱ���FILES�м�¼�İ�
// �����в������Ǳ����޸��ˣ� ��ô����STATS�Ӽ�¼�İ汾
// �ͱ��ص��ļ����в��
// ����".c"�ļ���˵��STATS �м�¼���Ƕ�����".b"�ļ���ʱ�䣬
// ������".c"�ļ���ʱ�䣬����FILES ��¼��ȴ��".c"�ļ���ʱ�䣬
// ��һ����Ҫע�⡣Ϊʲô��ô����������Ϊʵ���ϱ����޸���Դ
// �ļ�������Ҫ��ֻҪ�����ƴ���û���޸ļ��ɡ������������� c
// �ļ��汾ʵ�������ڷ������ϵĶ������ļ��İ汾���������²�
// �Ͳ�һ�����𣿵�ȷ����������Ϊ�ڷ������ϼ�ʹ".c"�ļ�û��
// �޸ģ�".b"�ļ���Ȼ�п��ܱ仯����˴��Ͷ������ļ��İ汾��
// �������壬����Ƿ������Ϳͻ��˲�֮ͬ����
void syn_load_file(string file, int ver)
{
	int len;
	mixed st;
	int ft, now_ft;

	switch (file_size(file))
	{
	case -2:
		// ����������ֵ�Ŀ¼��ɾ��֮
		log_file("version", sprintf("%s remove directory: %s\n",
					    log_time(), file));
		RM_CMD->rm_dir(file);
		break;
	case -1:
		break;
	default:
		// û������ļ����������������ļ�
		// ���ȱȽϱ��غͷ������ϵİ汾���������ͬ
		// ����Ҫ���¡�����Ƚϱ��صİ汾��Ϣ����ʵ
		// �ļ�����Ϣ�����ʱ�䲻��ͬ����Ҳ��Ҫ���¡�
		st = stat(file);
		if (! arrayp(st) || sizeof(st) < 3)
			ft = -1;
		else
			ft = st[1];

		// ȡ�����ļ��ļ�¼ʱ��
		now_ft = query_temp(STATS + file);
		if (now_ft == ft && query_temp(FILES + file) == ver)
		{
			// �͵�ǰ�İ汾һ��������Ҫ����
			DEBUG_LOG(sprintf("file(%s) local = %d  ver = %d  stat = %d  ft = %d\n",
					  file, query_temp(FILES + file), ver, query_temp(STATS + from), ft));
			set(STATS + file, now_ft);
			return;
		}

		break;
	}

	len = strlen(file) - 2;
	if (len > 0 && file[len] == '.' && file[len + 1] == 'c')
	{
		// ��Դ�ļ����ȴ���һ���յ��ļ���һ����˵��
		// �����᷵��һ���������ļ�����������Ҫ����
		// ��Դ�ļ����������Ż᷵��Դ���롣
		rm(file);
		write_file(file, "// C source file\n", 1);
	}

	// ��ȡ����ļ��İ汾���������Ҫ����Դ����İ汾��
	// ��ô�������᷵��һ��Դ���򣬷���������᷵��һ��
	// BINARY�ļ���
	syn_get_file(file);
}

static int d = 0;

// ���ĳһ��·��
private void syn_load_version(string path, mapping store)
{
	mixed *dirs;
	string *files;
	string *outs;
	mixed rmfile;
	string full_name;
	string bin_name;
	string get_file;
	int ver;
	int len;

	if (mapp(query(FILES + path)))
		// ͬ��һ��·���İ汾
		; else
	if (! undefinedp(ver = query(FILES + path)))
	{
		// ͬ��һ���ļ��İ汾
		syn_load_file(path, ver);
		return;
	} else
		// û������ļ�������ͬ��
		return;

	if (path[strlen(path) - 1] != '/') path += "/";

	sys_info(sprintf("check version: %s", path));

	// ��ñ���·�����ļ�
	dirs = get_dir(path, -1);

	// ��ð汾���ϵ������ļ�
	if (! mapp(store))
	{
		sys_info(sprintf("path %s isn't valid directory.", path));
		return;
	}
	files = keys(store);

	// �ҳ����ض�����ļ���Ŀ¼�������������������İ汾
	// ��û�У����Ҳ����ڱ��ز���Ҫ���µ�·��
	outs = filter_array(dirs, (: undefinedp($(store)[((mixed *) $1)[0]]) &&
				     member_array($(path) + ((mixed *) $1)[0], exclude_dir) == -1 :));

	// ɾ����Щ�ļ���Ŀ¼
	foreach (rmfile in outs)
	{
		reset_eval_cost();
		if (rmfile[1] == -2)
		{
			// ����һ��Ŀ¼
			log_file("version", sprintf("%s remove directory: %s\n",
						    log_time(), path + rmfile[0]));

			RM_CMD->rm_dir(path + rmfile[0]);
		} else
		{
			// ����һ����ͨ�ļ���ɾ��֮
			log_file("version", sprintf("%s remove file: %s\n",
						    log_time(), path + rmfile[0]));
			// More to be added
			len = strlen(rmfile[0]) - 2;
			if (len > 0 && rmfile[0][len] == '.' &&
			    rmfile[0][len + 1] == 'c')
			{
				// �����c�ļ���ͬʱɾ��bin�ļ�
				rm(bin_path + path + rmfile[0][0..len] + "b");
			}

			rm(path + rmfile[0]);
		}
		// ����ɾ������ص��ļ�
	}

	// ��ȡ��Ҫ���µ��ļ�
	foreach (get_file in files)
	{
		reset_eval_cost();
		full_name = path + get_file;
		if (mapp(store[get_file]))
		{
			// ����һ��·�����������û�У��ͽ���
			switch (file_size(full_name))
			{
			case -2:
				// �Ѿ��������Ŀ¼
				break;

			case -1:
				// û�����Ŀ¼��ͬ�����ļ�
				mkdir(full_name);
				break;

			default:
				// ��������ֵ��ļ�
				rm(full_name);
				mkdir(full_name);
				break;
			}

			// ��binaries����Ҳ����һ��·�� ����
			bin_name = bin_path + full_name;
			switch (file_size(bin_name))
			{
			case -2:
				// BIN�����Ѿ��������Ŀ¼
				break;

			case -1:
				// û�����Ŀ¼�����ļ�
				mkdir(bin_name);
				break;

			default:
				// ��������ֵ��ļ�
				rm(bin_name);
				mkdir(bin_name);
			}

			if (member_array(full_name, exclude_dir) == -1)
				// ����ͬ����һ��Ŀ¼�İ汾
				syn_load_version(full_name, store[get_file]);
		} else
		{
			// ����һ����ͨ�ļ�
			syn_load_file(full_name, store[get_file]);
		}
	}

	// ����Ƕ�����Ҫ���µ��ļ����Ǳ�Ŀ¼���ڲ������һ
	// �࣬������Щ�ļ���
	files = filter_array(files, (: member_array($(path) + $1, include_dir) != -1 ||
				       member_array($(path), exclude_dir) :));
}

// ͬ���汾����
// ����ʱ���ܳɹ���ͬ���ˣ�Ҳ����û�С�
private void syn_finish()
{
	string op;

	sys_info(sprintf("ͬ���������汾״̬ = %d", version_ok));

	if (vfd) { socket_close(vfd); vfd = 0; }

	client_info[STATUS] = STATUS_FINISHED;
	client_info[FILE_NAME] = 0;
	client_info[FILE_POS] = 0;
	client_info[FILE_SIZE] = 0;
	client_info[PENDING_WRITE] = ({ });
	client_info[RESULT_BUFFER] = "";

	// �����ʱ����
	delete_temp(FILES);
	delete_temp(STATS);

	// ȡoperator
	op = query_temp("operator");
	delete_temp("operator");

	// ����汾�Ѿ�ͬ�����ˣ���ֱ�ӷ���
	if (version_ok)
	{
		if (stringp(op)) return;

		// ����ϵͳ�Զ�ͬ���İ汾����Ҫ������������
		if (query_temp("version_changed"))
		{
			message_system("ϵͳ�����˰汾��������ʮ�����Ժ���������������\n");
			call_out("syn_reboot_mud", 30);

			// �������ð汾Ϊ��Ч
			version_ok = 0;
		}
		return;
	}

	// �����������ͬ������ô�����ð汾��Ϊ�㣬��ʾ��Ҫ
	// ����ͬ����������������MUD��
	if (stringp(op))
	{
		set("VERSION_NO", 0);
		save();
		delete_temp("operator");
		sys_info(sprintf("%sͬ���汾�Ĳ���ʧ���ˣ�����"
				 "��鿴��־(version)��", op));

		// �����ڵİ汾Ϊ��Ч
		version_ok = 1;
	} else
	{
		set("VERSION_NO", 0);
		save();
		// һ�����Ժ���������MUD
		sys_info("ͬ���汾ʧ�ܣ�����һ���Ӻ���������MUD��");
		call_out("syn_reboot_mud", 60);
	}
}

// ͬ��ʧ�ܣ���������MUD
private void syn_reboot_mud()
{
	sys_info("�汾������������MUD��");
	shutdown(0);
}

// ����ͻ��˽��յ������Է�����������
private void syn_read_callback(int fd, buffer buf)
{
	string str;
	int len;
	int ver;
	string msg;

	if (fd != vfd || ! bufferp(buf)) return;

	DEBUG_LOG(sprintf(HIC "incoming: buf = %O(%d)"NOR"\n", buf, sizeof(buf)));

	do
	{
		if (! client_info[FILE_NAME])
		{
			// û���ļ����֣����յ�����ͨӦ����Ϣ
	
			// ������Ӧ�ôӻ������ж������ֽ���Ŀ����Ϊ
			// ���ܲ���һ�λ����ͨ��Ӧ����Ϣ������ҽ�
			// ��Щ��Ϣ�ۼƵ�RESULT_BUFFER�У� һֱ����
			// ���������ֽ�Ϊֹ����ô����δӻ���������
			// ����Ӧ���Ƕ��ٸ��ֽڣ���Ӧ�ü��㡣���б�
			// ����FILE_POS�е������Ѿ��������ַ���
			len = NORMAL_RESULT_LEN - client_info[FILE_POS];
			if (len > sizeof(buf))
				// ���û����ô���ֽڿ������Ҷ�
				len = sizeof(buf);
			client_info[FILE_POS] += len;
			client_info[RESULT_BUFFER] += read_buffer(buf, 0, len);
			// ȡʣ���buffer
			buf = buf[len..<1];
	
			if (client_info[FILE_POS] >= NORMAL_RESULT_LEN)
			{
				// ������һ��ͨ���ķ�����Ϣ��������
				// �û�������
				str = client_info[RESULT_BUFFER];
				client_info[RESULT_BUFFER] = "";
				client_info[FILE_POS] = 0;
	
				// ������յ��Ľ����Ϣ
				syn_receive_result(str);
			}
		}
	
		DEBUG_LOG(sprintf("buf = %O(%d) ... file_name = %O(%d)\n",
							  buf, sizeof(buf),
							  client_info[FILE_NAME],
							  client_info[FILE_POS]));
		if (bufferp(buf) && client_info[FILE_NAME])
			// �����ļ�
			buf = buf[syn_receive_file(buf)..<1];

		// ���buf��Ϊ�գ����������
	} while (sizeof(buf) && client_info[STATUS] != STATUS_FINISHED);
}

// ͬ��ʱ�ͻ������ӵ�д�ص�����
void syn_write_callback(int fd)
{
	if (fd != vfd)
	{
		log_file("version", sprintf("socket error: fd = %d vfd = %d\n", fd, vfd));
		return;
	}

	while (sizeof(client_info[PENDING_WRITE]))
	{
		// ����������Ϣ������֮
		if (send_client_pending_msg() != 0)
			// û�гɹ��ķ��ͣ��ȴ���һ�η���
			return;
	}

	// ���ݵ�ǰ��״̬����
	switch (client_info[STATUS])
	{
	case STATUS_CONNECTING:
		if (fetch_file_list)
		{
			// ָ�����ĳЩ�ļ�
			syn_fetch_file_from_server();
			break;
		}

		// �ո����ӣ�����ȡ�汾������
		send_command(fd, sprintf("getver from %s(%s)",
					 LOCAL_MUD_NAME(), INTERMUD_MUD_NAME,
					 __PORT__));
		client_info[STATUS] = STATUS_GET_VERSION;
		sys_info("�汾����ɹ��ĺͷ�����������ͨѶ��");
		break;
	}
}

// ͬ��ʱ�ͻ������ӶϿ��Ļص�����
private void syn_close_callback(int fd)
{
	if (fd != vfd) return;

	vfd = 0;
	if (version_ok) return;

	// �汾û��ͬ����ȫ��TCP�����Ѿ��Ͽ�
	syn_finish();
	log_file("version", sprintf("%s TCP connection lost when synchronizing.\n",
				    log_time()));
	DEBUG_LOG(HIG "TCP disconnected."NOR"\n");
}

// ϵͳ��Ϣ
private void sys_info(string msg)
{
	CHANNEL_D->do_channel(this_object(), "sys", msg);
}

// ������Ϣ
private void debug_info(string msg)
{
	CHANNEL_D->do_channel(this_object(), "debug", msg);
}

// �汾����վ�������Է�վ������
private void in_listen_callback(int fd)
{
	int new_fd;
	string address;
	string ip;
	int port;

	if ((new_fd = socket_accept(fd, "in_read_callback",
					"in_write_callback")) < 0)
		// û�гɹ��Ľ��������������
		return;

	address = socket_address(new_fd);
	if (! stringp(address) || sscanf(address, "%s %d", ip, port) != 2 ||
	    member_array(ip, AGENT_IP) == -1)
	{
		// �����ַû�о�����Ȩ
		socket_close(new_fd);
		return;
	}

	sys_info(sprintf("վ�� %s ���Ӱ汾��ʼͬ���汾��", ip));

	socket_info[new_fd] = allocate(8);
	socket_info[new_fd][STATUS] = STATUS_LOGIN;
	socket_info[new_fd][CMD_BUFFER] = "";
	socket_info[new_fd][CMD_QUEUE] = ({ });
	socket_info[new_fd][PENDING_WRITE] = ({ });
	socket_info[new_fd][SUB_SITES] = "����";

	// ����״̬
	socket_info[new_fd][STATUS] = STATUS_WAIT_COMMAND;
	in_write_callback(new_fd);
}

// ������Ϣ
private void in_read_callback(int fd, mixed mess)
{
	int cc;
	string *cmds;
	mixed  prefix;
	string str;

	if (! arrayp(socket_info[fd]))
		return;

	if (stringp(mess))
		// ���յ����ַ���
		str = mess;
	else
	if (bufferp(mess))
		// ���յ��˻�����
		str = read_buffer(mess, 0, sizeof(mess));
	else
		return;

	if (! str) return;

	str = replace_string( str, "\r", "");
	if (stringp(prefix = socket_info[fd][CMD_BUFFER]))
		str = (string) prefix + str + "\n";
	else
		str += "\n";

	cmds = explode(str, "\n");
	socket_info[fd][CMD_BUFFER] = cmds[sizeof(cmds) - 1];

	if (sizeof(cmds) > 1)
	{
		// ����Щ������뵽���������
		cc = sizeof(socket_info[fd][CMD_QUEUE]);
		socket_info[fd][CMD_QUEUE] += cmds[0..<2];
		if (socket_info[fd][STATUS] == STATUS_WAIT_COMMAND)
			// ���ڽ�������״̬
			parse_cmd(fd);
	}
}

// �ɹ�д��
private void in_write_callback(int fd)
{
	buffer buf;
	int pos, len;
	int i;

	for (i = 0; i < 32; i++)
	{
		// ѭ��������Ϣ
		reset_eval_cost();

		// �Ѿ��������ˣ�
		if (! arrayp(socket_info[fd]))
			// �ǣ��������Ҫ����������
			return;

		// �������������ͨ��Ϣ�����ҷ��ͳ�ȥ
		while (sizeof(socket_info[fd][PENDING_WRITE]))
		{
			// ����������Ϣ������֮
			if (send_pending_msg(fd) != 0)
				// û�гɹ��ķ��ͣ��ȴ���һ�η���
				return;
		}

		// ���ݵ�ǰ��״̬���н�һ������
		switch (socket_info[fd][STATUS])
		{
		case STATUS_SENDING:
			// ���ڷ����ļ�
			pos = socket_info[fd][FILE_POS];
			len = socket_info[fd][FILE_SIZE] - pos;
			if (len > FILE_BLOCK)
				len = FILE_BLOCK;
			if (len > 0)
			{
				buf = read_buffer((string) socket_info[fd][FILE_NAME], pos, len);
				if (sizeof(buf) != len)
					// ��ȡû����ȫ�ɹ�����д�㷢�͡�
					buf = allocate_buffer(len);
				// �ж���β����Ľ��
				switch (socket_write(fd, buf))
				{
				case EESUCCESS:
					// �ƶ��α�
					pos += len;
					break;

				case EECALLBACK:
					// �ƶ��α�
					pos += len;

					// �ȴ�CALLBACK���Ȳ���������
					socket_info[fd][FILE_POS] = pos;
					return;

				case EEWOULDBLOCK:
					// ����æ
					call_out("in_write_callback", 2, fd);
					return;

				default:
					// ����ʧ�ܣ��ȴ��´�callback
					return;
				}
			}

			// �ж��ļ��Ƿ������
			if ((socket_info[fd][FILE_POS] = pos) >=
			    socket_info[fd][FILE_SIZE])
			{
				// �ļ��Ѿ�������ϣ�����״̬
				socket_info[fd][STATUS] = STATUS_WAIT_COMMAND;
				if (! sizeof(socket_info[fd][CMD_QUEUE]))
					// �Ѿ�û�д������������
					return;

				// �����������ΪʲôҪ��
				// this_object() ���к��У�
				// ����ǲ���ʡ�Եģ���Ϊ��
				// ���������ֵĺ����Ϳ��Ը�
				// ��previous_object() �ֱ�
				// �Ƿ���������callback�ڡ�
				this_object()->parse_cmd(fd);

				// ������ѭ�����ᴦ����������Ľ��
			}

			// ���ʹ������
			break;
	
		default:
			// δ����״̬���޲���
			return;
		}

		// һ�δ���(switch)��ϣ�ѭ����������
	}

	// ����̫����
	debug_info("�� SOCKET д������̫�࣬�ݻ���");
	call_out("in_write_callback", 1, fd);
}

// ���ӶϿ�
private void in_close_callback(int fd)
{
	string address;

	address = socket_address(fd);
	if (stringp(address))
		sscanf(address, "%s %*d", address);
	else
		address = "unknow";

	sys_info(sprintf("վ�� %s �ͱ�վ�Ͽ������ӡ�", address));

	// �����Ϣ
	map_delete(socket_info, fd);
}

// ��������
// ���ڽ�֧���������
// 1. getver [dbase]
// 2. get <file>
// 3. close
// ��������򵥣������ó�����﷨������
private void parse_cmd(int fd)
{
	string cmd;
	string word, arg;

	// ȡ��һ��������д���
	cmd = socket_info[fd][CMD_QUEUE][0];
	socket_info[fd][CMD_QUEUE] = socket_info[fd][CMD_QUEUE][1..<1];

	if (sscanf(cmd, "%s %s", word, arg) != 2)
	{
		word = cmd;
		arg = 0;
	}

	switch (word)
	{
	case "getver":
		cmd_getver(fd, arg);
		break;

	case "get":
		cmd_get(fd, arg);
		break;

	case "close":
		cmd_close(fd, arg);
		break;
	}
}

// ��ȡ�汾����
private void cmd_getver(int fd, string arg)
{
	string mudn;

	if (arrayp(total_build))
	{
		// ���ڰ汾���ڹ�����
		send_error_msg(fd, "generating version now.\n");
		return;
	}

	if (arg != "dbase")
	{
		// ���Ͱ汾��
		if (stringp(arg) && sscanf(arg, "from %s", mudn) == 1)
		{
			sys_info(sprintf("%s���ڶ�ȡ�汾�ţ�׼��ͬ���汾��", mudn));
			socket_info[fd][SUB_SITES] = mudn;
		}

		send_version(fd);
		return;
	}

	// �����ļ�
	send_file(fd, query_save_file() + __SAVE_EXTENSION__, "dbase");
}

// ��ȡĳһ���ļ�
private void cmd_get(int fd, string arg)
{
	string ban;
	int last;

	// �鿴�ļ�
	if (! arg || arg[0] != '/')
	{
		send_error_msg(fd, sprintf("no such file(%O).\n", arg));
		return;
	}

	last = strlen(arg) - 2;
	if (last >= 0 && arg[last] == '.' && arg[last + 1] == 'c')
	{
		// C�ļ����쿴�Ƿ�����Ҫ�����汾�ģ�������ǣ�
		// �򷵻�BIN�ļ���
		if (! is_need_release_source(arg))
			arg = bin_path + arg[0..last] + "b";
	}

	// ���Ͱ汾��¼�µ��ļ�
	send_file(fd, VERSION_DIR + arg, arg);
}

// �ر�����
private void cmd_close(int fd, string arg)
{
	string address;

	address = socket_address(fd);
	if (stringp(address))
		sscanf(address, "%s %*d", address);
	else
		address = "unknow";

	sys_info(sprintf("վ�� %s �ͱ�վͬ����ϡ�", address));

	send_result(fd, RESULT_FINISH "ok\n");
}

// ��Է�����һ���ļ�
private void send_file(int fd, string file, string peer_name)
{
	int fs;

	// ֱ�ӷ���
	if ((fs = file_size(file)) < 0)
	{
		send_error_msg(fd, sprintf("read file(%s) error.\n", file));
		return;
	}

	// ����״̬��Ȼ�����ȷ����ļ��ĳ���
	socket_info[fd][FILE_NAME] = file;
	socket_info[fd][FILE_SIZE] = fs;
	socket_info[fd][FILE_POS] = 0;
	socket_info[fd][STATUS] = STATUS_SENDING;
	if (send_result(fd, sprintf(RESULT_FILE "%s %d\n", peer_name, fs)) == 0 &&
	    previous_object() != this_object())
		// �ɹ������˵�Ӧ�𣬲��ҵ�ǰ������in_write_callback
		// ���ý��룬����������ļ�
		in_write_callback(fd);
}

// ������������Ϣ
private int send_pending_msg(int fd)
{
	string result;

	result = socket_info[fd][PENDING_WRITE][0];

	switch (socket_write(fd, result))
	{
	case EESUCCESS:
		// ���ͳɹ���
		socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
		return 0;

	case EECALLBACK:
		// ��Ҫ�ȴ�
		socket_info[fd][PENDING_WRITE] = socket_info[fd][PENDING_WRITE][1..<1];
		return -1;

	case EEWOULDBLOCK:
		// ������������
		call_out("in_write_callback", 2, fd);
		return -1;

	default:
	}
}

// ��Է�����һ�������Ϣ
private int send_result(int fd, string msg)
{
	string result;

	result = sprintf("%-" + (NORMAL_RESULT_LEN - 1) + "s.", msg);

	if (sizeof(socket_info[fd][PENDING_WRITE]))
	{
		// �Ѿ���������Ҫ���͵������ˣ���η��͵���
		// ��������
		socket_info[fd][PENDING_WRITE] += ({ result });
		return -1;
	}

	switch (socket_write(fd, result))
	{
	case EESUCCESS:
		// ���ͳɹ���
		return 0;

	case EECALLBACK:
		// ��Ҫ�ȴ�
		// socket_info[fd][PENDING_WRITE] += ({ result });
		return -1;

	case EEWOULDBLOCK:
		// ������������
		socket_info[fd][PENDING_WRITE] += ({ result });
		call_out("in_write_callback", 2, fd);
		return -1;

	default:
		socket_close(fd);
	}
}

// ��Է�����һ��������Ϣ
private int send_error_msg(int fd, string msg)
{
	return send_result(fd, RESULT_ERR + msg);
}

// ��ĳһ�����������Ͱ汾��
private void send_version(int fd)
{
	int ver;
	string msg;

	if (! intp(ver = query("VERSION_NO")) || ! ver)
	{
		// ��û�а汾��
		send_result(fd, RESULT_NO_VERSION "no version");
		remove_connection(fd);
		return;
	}

	send_result(fd, sprintf(RESULT_VERSION "%d\n", ver));
}

// ȥ��һ��������Ϣ
private void remove_connection(int fd)
{
	map_delete(socket_info, fd);
	socket_close(fd);
}

// Ϊһ���ļ����ӱ�֤�����ļ���ID
int append_sn(string file)
{
	string ckey;
	string text;
	int len;

	switch (file_valid(file))
	{
	case 0:
		// Ŀǰ�ļ��� ID �Ǵ����
		text = read_file(file);
		len = strsrch(text, "\n");
		text = text[len + 1..<1];
		write_file(file, text, 1);

		// ɾ������ID�Ժ��������ִ��

	case -2:
		// Ŀǰû�м���ID
		ckey = file_crypt(file);
		text = read_file(file);
		text = sprintf("// SN:%s\n%s", ckey, text);
		write_file(file, text, 1);
		return 1;

	case -1:
		// û������ļ�
		return -1;

	default:
		// �Ѿ�������ȷ�ļ���ID
		return 1;
	}
}
